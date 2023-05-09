/* GDB code to parse PDB debug files.
   Copyright (C) 2023 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "defs.h"
#include "symtab.h"
#include "symfile.h"
#include "objfiles.h"
#include "buildsym.h"
#include "complaints.h"
#include "coff/i386.h"
#include "coff/external.h"
#include "pdbread.h"

struct pdb_type
{
  file_ptr offset;
  uint16_t kind;
};

static void
pdb_new_init (struct objfile *ignore)
{
}

static void
pdb_symfile_init (struct objfile *objfile)
{
}

/* Map the PDB builtin types to GDB's.  */
static struct type *
pdb_builtin_type (const struct builtin_type *builtin, uint32_t t)
{
  switch (t)
    {
    case T_CHAR:
    case T_INT1:
      return builtin->builtin_char;

    case T_UCHAR:
    case T_UINT1:
      return builtin->builtin_unsigned_char;

    case T_SHORT:
    case T_INT2:
      return builtin->builtin_short;

    case T_USHORT:
    case T_UINT2:
      return builtin->builtin_unsigned_short;

    case T_LONG:
      return builtin->builtin_long;

    case T_ULONG:
      return builtin->builtin_unsigned_long;

    case T_INT4:
      return builtin->builtin_int;

    case T_UINT4:
      return builtin->builtin_unsigned_int;

    case T_QUAD:
    case T_INT8:
      return builtin->builtin_long_long;

    case T_UQUAD:
    case T_UINT8:
      return builtin->builtin_unsigned_long_long;
    }

  return NULL;
}

/* Return the size in bytes of a PDB builtin type.  */
static ULONGEST
pdb_builtin_type_length (uint32_t t)
{
  switch (t)
    {
    case T_CHAR:
    case T_INT1:
    case T_UCHAR:
    case T_UINT1:
      return 1;

    case T_SHORT:
    case T_INT2:
    case T_USHORT:
    case T_UINT2:
      return 2;

    case T_LONG:
    case T_ULONG:
    case T_INT4:
    case T_UINT4:
      return 4;

    case T_QUAD:
    case T_INT8:
    case T_UQUAD:
    case T_UINT8:
      return 8;
    }

  return 0;
}

/* Some integers, such as enum values, get stored as an extended value if
   they're too large to fit into two bytes.  The two bytes that would normally
   be the value are instead a type indicator, and the actual value follows.  */
static bool
pdb_read_extended_value (uint16_t kind, char **ptr, uint16_t *length,
			 LONGEST *ret)
{
  switch (kind)
  {
  case LF_CHAR:
    if (*length < 1)
      return false;

    *ret = *(signed char*) *ptr;
    (*ptr)++;
    (*length)--;

    break;

  case LF_SHORT:
    if (*length < sizeof (int16_t))
      return false;

    *ret = (int16_t) bfd_getl16 (*ptr);
    *ptr += sizeof (int16_t);
    *length -= sizeof (int16_t);

    break;

  case LF_USHORT:
    if (*length < sizeof (uint16_t))
      return false;

    *ret = bfd_getl16 (*ptr);
    *ptr += sizeof (uint16_t);
    *length -= sizeof (uint16_t);

    break;

  case LF_LONG:
    if (*length < sizeof (int32_t))
      return false;

    *ret = (int32_t) bfd_getl32 (*ptr);
    *ptr += sizeof (int32_t);
    *length -= sizeof (int32_t);

    break;

  case LF_ULONG:
    if (*length < sizeof (uint32_t))
      return false;

    *ret = bfd_getl32 (*ptr);
    *ptr += sizeof (uint32_t);
    *length -= sizeof (uint32_t);

    break;

  case LF_QUADWORD:
    if (*length < sizeof (int64_t))
      return false;

    *ret = (int64_t) bfd_getl64 (*ptr);
    *ptr += sizeof (int64_t);
    *length -= sizeof (int64_t);

    break;

  case LF_UQUADWORD:
    if (*length < sizeof (uint64_t))
      return false;

    *ret = bfd_getl64 (*ptr);
    *ptr += sizeof (uint64_t);
    *length -= sizeof (uint64_t);

    break;

  default:
    return false;
  }

  return true;
}

/* Read an LF_FIELDLIST entry for an enum.  This can have two possible subtypes:
   LF_ENUMERATE, for a value, and LF_INDEX, which points to an overflow
   fieldlist if this one gets too large.  */
static void
pdb_read_enum_fieldlist (std::vector<struct field> &fields, bfd *tpi,
			 struct pdb_type *types, uint32_t fieldlist_type,
			 uint32_t first_type, uint32_t last_type)
{
  struct pdb_type *type;
  char int_buf [sizeof (uint16_t)];
  uint16_t length;
  char *buf, *ptr;

  if (fieldlist_type < first_type || fieldlist_type > last_type)
    return;

  type = &types [fieldlist_type - first_type];

  if (type->kind != LF_FIELDLIST)
    return;

  if (bfd_seek (tpi, type->offset, SEEK_SET) != 0)
    return;

  if (bfd_bread (int_buf, sizeof (int_buf), tpi) != sizeof (int_buf))
    return;

  length = bfd_getl16 (int_buf);

  if (length <= sizeof (uint16_t))
    return;

  buf = (char *) xmalloc (length);

  if (bfd_bread (buf, length, tpi) != length)
    goto end;

  /* Skip LF_FIELDLIST value.  */
  ptr = buf + sizeof (uint16_t);
  length -= sizeof (uint16_t);

  while (length >= sizeof (uint16_t))
    {
      uint16_t sub_type;

      sub_type = bfd_getl16 (ptr);
      ptr += sizeof (uint16_t);
      length -= sizeof (uint16_t);

      switch (sub_type)
	{
	case LF_ENUMERATE: {
	  struct lf_enumerate *en;
	  LONGEST val;
	  size_t name_len;
	  char *name;

	  if (length < sizeof (*en))
	    goto end;

	  en = (struct lf_enumerate *) ptr;

	  ptr += sizeof (*en);
	  length -= sizeof (*en);

	  val = bfd_getl16 (&en->value);

	  /* Extended value - actual value follows.  */
	  if (val >= 0x8000)
	    {
	      if (!pdb_read_extended_value (val, &ptr, &length, &val))
		goto end;
	    }

	  name_len = strnlen (ptr, length);

	  /* Should be zero-terminated.  */
	  if (name_len == length)
	    goto end;

	  name = ptr;
	  ptr += name_len + 1;
	  length -= name_len + 1;

	  if (name_len != 0)
	    {
	      fields.emplace_back ();
	      struct field &field = fields.back ();
	      field.set_name (xstrdup (name));
	      field.set_loc_enumval (val);
	    }

	  /* Round to 4-byte boundary.  */
	  if ((ptr - buf + 2) % 4)
	    {
	      if (length < 4)
		goto end;

	      length -= 4 - ((ptr - buf + 2) % 4);
	      ptr += 4 - ((ptr - buf + 2) % 4);
	    }

	    break;
	  }

	case LF_INDEX: {
	  struct lf_index *ind;
	  uint32_t fl_type;

	  if (length < sizeof (*ind))
	    goto end;

	  ind = (struct lf_index *) ptr;

	  ptr += sizeof (*ind);
	  length -= sizeof (*ind);

	  fl_type = bfd_getl32 (&ind->index);

	  pdb_read_enum_fieldlist (fields, tpi, types, fl_type, first_type,
				   last_type);

	  break;
	}

	default:
	  goto end;
	}
    }

end:
  free (buf);
}

/* Parse an LF_ENUM record, and add it as an enum symbol.  */
static void
pdb_add_enum (struct objfile *objfile, buildsym_compunit &builder,
	      bfd *tpi, struct pdb_type *types, uint32_t type_off,
	      uint32_t first_type, uint32_t last_type)
{
  char int_buf [sizeof (uint16_t)];
  uint16_t length;
  struct lf_enum en;
  struct type *t;
  struct symbol *sym;
  size_t name_len;
  char *name;
  std::vector<struct field> fields;
  struct pdb_type *type = &types [type_off];

  if (bfd_seek (tpi, type->offset, SEEK_SET) != 0)
    return;

  if (bfd_bread (int_buf, sizeof (int_buf), tpi) != sizeof (int_buf))
    return;

  length = bfd_getl16 (int_buf);

  if (length <= sizeof (en))
    return;

  if (bfd_bread (&en, sizeof (en), tpi) != sizeof (en))
    return;

  if (bfd_getl16 (&en.properties) & CV_PROP_FORWARD_REF)
    return;

  name_len = length - sizeof (en);
  name = (char * ) xmalloc (name_len + 1);

  if (bfd_bread (name, name_len, tpi) != name_len)
    {
      free (name);
      return;
    }

  /* Should be zero-terminated, but just in case.  */
  name[name_len] = 0;

  t = type_allocator (objfile).new_type ();
  t->set_code (TYPE_CODE_ENUM);
  t->set_name (name);

  t->set_target_type (pdb_builtin_type (builtin_type (objfile),
					bfd_getl32 (&en.underlying_type)));
  t->set_length (pdb_builtin_type_length (bfd_getl32 (&en.underlying_type)));

  pdb_read_enum_fieldlist (fields, tpi, types, bfd_getl32 (&en.field_list),
			   first_type, last_type);

  if (!fields.empty ())
    {
      t->set_num_fields (fields.size ());
      t->set_fields
	((struct field *)
	 TYPE_ALLOC (t, sizeof (struct field) * fields.size ()));
      memcpy (t->fields (), fields.data (),
	      sizeof (struct field) * fields.size ());
    }

  sym = new (&objfile->objfile_obstack) symbol;
  sym->set_language (language_c, &objfile->objfile_obstack);
  sym->set_domain (STRUCT_DOMAIN);
  sym->set_aclass_index (LOC_TYPEDEF);
  sym->set_linkage_name (name);
  sym->set_type (t);

  add_symbol_to_list (sym, builder.get_global_symbols ());
}

/* Read and parse the TPI stream, which contains the type definitions.  */
static bool
pdb_read_tpi_stream (struct objfile *objfile, buildsym_compunit &builder)
{
  bfd *tpi;
  struct pdb_tpi_stream_header h;
  uint32_t first_type, last_type, num_types;
  struct pdb_type *types;

  tpi = bfd_get_elt_at_index (objfile->obfd.get (), PDB_TPI_STREAM_NUM);

  if (!tpi)
    return false;

  if (bfd_seek (tpi, 0, SEEK_SET) != 0)
    {
      bfd_close (tpi);
      return false;
    }

  if (bfd_bread (&h, sizeof (h), tpi) != sizeof (h))
    {
      bfd_close (tpi);
      return false;
    }

  if (bfd_getl32 (&h.version) != TPI_STREAM_VERSION_80)
    {
      bfd_close (tpi);
      return false;
    }

  if (bfd_seek (tpi, bfd_getl32 (&h.header_size), SEEK_SET) != 0)
    {
      bfd_close (tpi);
      return false;
    }

  first_type = bfd_getl32 (&h.type_index_begin);
  last_type = bfd_getl32 (&h.type_index_end) - 1;

  if (last_type <= first_type)
    {
      bfd_close (tpi);
      return true;
    }

  num_types = last_type - first_type + 1;
  types = (struct pdb_type *) xmalloc (sizeof (*types) * num_types);

  for (unsigned int i = 0; i < num_types; i++)
    {
      char int_buf[sizeof (uint16_t)];
      uint16_t length;

      types[i].offset = bfd_tell(tpi);

      if (bfd_bread (int_buf, sizeof (int_buf), tpi) != sizeof (int_buf))
	{
	  free (types);
	  bfd_close (tpi);
	  return false;
	}

      length = bfd_getl16 (int_buf);

      if (length < sizeof (uint16_t))
	{
	  free (types);
	  bfd_close (tpi);
	  return false;
	}

      if (bfd_bread (int_buf, sizeof (int_buf), tpi) != sizeof (int_buf))
	{
	  free (types);
	  bfd_close (tpi);
	  return false;
	}

      types[i].kind = bfd_getl16 (int_buf);

      if (bfd_seek (tpi, length - sizeof (uint16_t), SEEK_CUR) != 0)
	{
	  free (types);
	  bfd_close (tpi);
	  return false;
	}
    }

  for (unsigned int i = 0; i < num_types; i++)
    {
      switch (types[i].kind)
	{
	case LF_ENUM:
	  pdb_add_enum (objfile, builder, tpi, types, i, first_type, last_type);
	  break;

	default:
	  break;
	}
    }

  free (types);

  bfd_close (tpi);

  return true;
}

static void
pdb_symfile_read (struct objfile *objfile, symfile_add_flags symfile_flags)
{
  buildsym_compunit builder(objfile, "", nullptr, language_c, 0);

  if (!pdb_read_tpi_stream (objfile, builder))
    complaint (_("Failed to read types stream"));

  builder.end_compunit_symtab (0);
}

static void
pdb_symfile_finish (struct objfile *objfile)
{
}

static const struct sym_fns pdb_sym_fns =
{
  pdb_new_init,			/* sym_new_init: init anything gbl to
				   entire symtab */
  pdb_symfile_init,		/* sym_init: read initial info, setup
				   for sym_read() */
  pdb_symfile_read,		/* sym_read: read a symbol file into
				   symtab */
  pdb_symfile_finish,		/* sym_finish: finished with file,
				   cleanup */
  default_symfile_offsets,	/* sym_offsets: xlate external to
				   internal form */
  default_symfile_segments,	/* sym_segments: Get segment
				   information from a file */
  NULL,                         /* sym_read_linetable  */

  default_symfile_relocate,	/* sym_relocate: Relocate a debug
				   section.  */
  NULL,				/* sym_probe_fns */
};

void _initialize_pdbread ();
void
_initialize_pdbread ()
{
  add_symtab_fns (bfd_target_pdb_flavour, &pdb_sym_fns);
}
