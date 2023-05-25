/* od-pe.c -- dump information about a PE object file.
   Copyright (C) 2011-2023 Free Software Foundation, Inc.
   Written by Tristan Gingold, Adacore and Nick Clifton, Red Hat.

   This file is part of GNU Binutils.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include <stddef.h>
#include <time.h>
#include "safe-ctype.h"
#include "bfd.h"
#include "objdump.h"
#include "bucomm.h"
#include "bfdlink.h"
#include "coff/internal.h"
#define L_LNNO_SIZE 4 /* FIXME: which value should we use ?  */
#include "coff/external.h"
#include "coff/pe.h"
#include "libcoff.h"
#include "libpei.h"

/* Index of the options in the options[] array.  */
#define OPT_FILE_HEADER 0
#define OPT_AOUT 1
#define OPT_SECTIONS 2
#define OPT_SYMS 3
#define OPT_RELOCS 4
#define OPT_LINENO 5
#define OPT_LOADER 6
#define OPT_EXCEPT 7
#define OPT_TYPCHK 8
#define OPT_TRACEBACK 9
#define OPT_TOC 10
#define OPT_LDINFO 11

/* List of actions.  */
static struct objdump_private_option options[] =
  {
    { "header", 0 },
    { "aout", 0 },
    { "sections", 0 },
    { "syms", 0 },
    { "relocs", 0 },
    { "lineno", 0 },
    { "loader", 0 },
    { "except", 0 },
    { "typchk", 0 },
    { "traceback", 0 },
    { "toc", 0 },
    { "ldinfo", 0 },
    { NULL, 0 }
  };

/* Simplified section header.  */
struct pe_section
{
  /* NUL terminated name.  */
  char name[9];

  /* Section flags.  */
  unsigned int flags;

  /* Offsets in file.  */
  ufile_ptr scnptr;
  ufile_ptr relptr;
  ufile_ptr lnnoptr;

  /* Number of relocs and line numbers.  */
  unsigned int nreloc;
  unsigned int nlnno;
};

/* Translation entry type.  The last entry must be {0, NULL}.  */

struct xlat_table
{
  unsigned int  val;
  const char *  name;
};

/* PE file flags.  */
static const struct xlat_table file_flag_xlat[] =
  {
    { IMAGE_FILE_RELOCS_STRIPPED,     "RELOCS STRIPPED"},
    { IMAGE_FILE_EXECUTABLE_IMAGE,    "EXECUTABLE"},
    { IMAGE_FILE_LINE_NUMS_STRIPPED,  "LINE NUMS STRIPPED"},
    { IMAGE_FILE_LOCAL_SYMS_STRIPPED, "LOCAL SYMS STRIPPED"},
    { IMAGE_FILE_AGGRESSIVE_WS_TRIM,  "AGGRESSIVE WS TRIM"},
    { IMAGE_FILE_LARGE_ADDRESS_AWARE, "LARGE ADDRESS AWARE"},
    { IMAGE_FILE_16BIT_MACHINE,       "16BIT MACHINE"},
    { IMAGE_FILE_BYTES_REVERSED_LO,   "BYTES REVERSED LO"},
    { IMAGE_FILE_32BIT_MACHINE,       "32BIT MACHINE"},
    { IMAGE_FILE_DEBUG_STRIPPED,      "DEBUG STRIPPED"},
    { IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP, "REMOVABLE RUN FROM SWAP"},
    { IMAGE_FILE_NET_RUN_FROM_SWAP,   "NET RUN FROM SWAP"},
    { IMAGE_FILE_SYSTEM,              "SYSTEM"},
    { IMAGE_FILE_DLL,                 "DLL"},
    { IMAGE_FILE_UP_SYSTEM_ONLY,      "UP SYSTEM ONLY"},
    { IMAGE_FILE_BYTES_REVERSED_HI,   "BYTES REVERSED HI"},
    { 0, NULL }
  };

/* PE section flags.  */
static const struct xlat_table section_flag_xlat[] =
  {
    { IMAGE_SCN_MEM_DISCARDABLE, "DISCARDABLE" },
    { IMAGE_SCN_MEM_EXECUTE,     "EXECUTE" },
    { IMAGE_SCN_MEM_READ,        "READ" },
    { IMAGE_SCN_MEM_WRITE,       "WRITE" },
    { IMAGE_SCN_TYPE_NO_PAD,     "NO PAD" },
    { IMAGE_SCN_CNT_CODE,        "CODE" },
    { IMAGE_SCN_CNT_INITIALIZED_DATA,   "INITIALIZED DATA" },
    { IMAGE_SCN_CNT_UNINITIALIZED_DATA, "UNINITIALIZED DATA" },
    { IMAGE_SCN_LNK_OTHER,       "OTHER" },
    { IMAGE_SCN_LNK_INFO,        "INFO" },
    { IMAGE_SCN_LNK_REMOVE,      "REMOVE" },
    { IMAGE_SCN_LNK_COMDAT,      "COMDAT" },
    { IMAGE_SCN_MEM_FARDATA,     "FARDATA" },
    { IMAGE_SCN_MEM_PURGEABLE,   "PURGEABLE" },
    { IMAGE_SCN_MEM_16BIT,       "16BIT" },
    { IMAGE_SCN_MEM_LOCKED,      "LOCKED" },
    { IMAGE_SCN_MEM_PRELOAD,     "PRELOAD" },
    { IMAGE_SCN_LNK_NRELOC_OVFL, "NRELOC OVFL" },
    { IMAGE_SCN_MEM_NOT_CACHED,  "NOT CACHED" },
    { IMAGE_SCN_MEM_NOT_PAGED,   "NOT PAGED" },
    { IMAGE_SCN_MEM_SHARED,      "SHARED" },    
    { 0, NULL }
  };


/* Display help.  */

static void
pe_help (FILE *stream)
{
  fprintf (stream, _("\
For PE files:\n\
  header      Display the file header\n\
  sections    Display the section headers\n\
"));
}

/* Return true if ABFD is handled.  */

static int
pe_filter (bfd *abfd)
{
  return bfd_get_flavour (abfd) == bfd_target_coff_flavour;
}

/* Display the list of name (from TABLE) for FLAGS, using comma to separate
   them.  A name is displayed if FLAGS & VAL is not 0.  */

static void
dump_flags (const struct xlat_table * table, unsigned int flags)
{
  unsigned int r = flags;
  bool first = true;
  const struct xlat_table *t;

  for (t = table; t->name; t++)
    if ((flags & t->val) != 0)
      {
        r &= ~t->val;

        if (first)
          first = false;
        else
          putchar (',');
        fputs (t->name, stdout);
      }

  /* Undecoded flags.  */
  if (r != 0)
    {
      if (!first)
        putchar (',');
      printf (_("unknown: 0x%x"), r);
    }
}

static void
decode_machine_number (unsigned int machine)
{
  switch (machine)
    {
    case IMAGE_FILE_MACHINE_ARM: printf ("ARM\n"); break;
    case IMAGE_FILE_MACHINE_ARM64: printf ("ARM64\n"); break;
    case IMAGE_FILE_MACHINE_I386: printf ("I386\n"); break;
    case IMAGE_FILE_MACHINE_POWERPC: printf ("POWERPC\n"); break;
    case IMAGE_FILE_MACHINE_LOONGARCH64: printf ("LOONGARCH64\n"); break;
    case IMAGE_FILE_MACHINE_AMD64: printf ("AMD64\n"); break;

      // FIXME: Add more machine numbers.
    default: printf (_("unknown\n"));
    }
}

/* Dump the file header.  */

static void
dump_pe_file_header (bfd * abfd, struct external_PEI_filehdr * fhdr)
{
  printf (_("\nPEI File Header:\n"));
  printf (_("  Magic:         %#x\t\t- IMAGE_DOS_SIGNATURE\n"), (int) bfd_h_get_16 (abfd, fhdr->e_magic));

  unsigned int machine = (int) bfd_h_get_16 (abfd, fhdr->f_magic);
  printf (_("  Machine Num:   %#x\t\t- "), machine);
  decode_machine_number (machine);

  printf (_("  Num sections:  %d\n"), (int) bfd_h_get_16 (abfd, fhdr->f_nscns));

  long timedat = bfd_h_get_32 (abfd, fhdr->f_timdat);
  printf (_("  Time and date: 0x%08lx\t- "), timedat);
  if (timedat == 0)
    printf (_("not set\n"));
  else
    {
      /* Not correct on all platforms, but works on unix.  */
      time_t t = timedat;
      fputs (ctime (& t), stdout);
    }

  printf (_("  Symbols off:   0x%08lx\n"), (long) bfd_h_get_32 (abfd, fhdr->f_symptr));
  printf (_("  Num symbols:   %ld\n"), (long) bfd_h_get_32 (abfd, fhdr->f_nsyms));
  printf (_("  Opt hdr sz:    %d\n"), (int) bfd_h_get_16 (abfd, fhdr->f_opthdr));

  unsigned int flags = (int) bfd_h_get_16 (abfd, fhdr->f_flags);
  printf (_("  flags:         0x%04x\t\t- "), flags);
  dump_flags (file_flag_xlat, flags);

  putchar ('\n');
}

/* Dump the sections header.  */

static void
dump_pe_sections_header (bfd * abfd, struct external_PEI_filehdr * hdr)
{
  unsigned int off;
  unsigned int opthdr = (unsigned int) bfd_h_get_16 (abfd, hdr->f_opthdr);
  unsigned int n_scns = (unsigned int) bfd_h_get_16 (abfd, hdr->f_nscns);

  off = sizeof (struct external_PEI_filehdr) + opthdr;

  printf (_("\nSection headers (at %u+%u=0x%08x to 0x%08x):\n"),
          (unsigned int) sizeof (struct external_PEI_filehdr), opthdr, off,
          off + (unsigned int) sizeof (struct external_scnhdr) * n_scns);

  if (n_scns == 0)
    {
      printf (_("  No section headers\n"));
      return;
    }
  if (bfd_seek (abfd, off, SEEK_SET) != 0)
    {
      non_fatal (_("cannot seek to section headers start\n"));
      return;
    }

  /* We don't translate this string as it consists of field names.  */
  if (wide_output)
    printf (" # Name     paddr    vaddr    size     scnptr   relptr   lnnoptr  nrel  nlnno   Flags\n");
  else
    printf (" # Name     paddr    vaddr    size     scnptr   relptr   lnnoptr  nrel  nlnno\n");

  unsigned int i;
  for (i = 0; i < n_scns; i++)
    {
      struct external_scnhdr scn;
      unsigned int flags;

      if (bfd_bread (& scn, sizeof (scn), abfd) != sizeof (scn))
        {
          non_fatal (_("cannot read section header"));
          return;
        }

      printf ("%2d %-8.8s %08x %08x %08x %08x %08x %08x %-5d %-5d",
              i + 1, scn.s_name,
              (unsigned int) bfd_h_get_32 (abfd, scn.s_paddr),
              (unsigned int) bfd_h_get_32 (abfd, scn.s_vaddr),
              (unsigned int) bfd_h_get_32 (abfd, scn.s_size),
              (unsigned int) bfd_h_get_32 (abfd, scn.s_scnptr),
              (unsigned int) bfd_h_get_32 (abfd, scn.s_relptr),
              (unsigned int) bfd_h_get_32 (abfd, scn.s_lnnoptr),
              (unsigned int) bfd_h_get_16 (abfd, scn.s_nreloc),
              (unsigned int) bfd_h_get_16 (abfd, scn.s_nlnno));

      flags = bfd_h_get_32 (abfd, scn.s_flags);
      if (wide_output)
	printf (_("   %08x "), flags);
      else
	printf (_("\n            Flags: %08x: "), flags);

      if (~flags == 0)
        {
          /* Stripped executable ?  */
          putchar ('\n');
        }
      else
        {
	  flags &= ~ IMAGE_SCN_ALIGN_POWER_BIT_MASK;
          dump_flags (section_flag_xlat, flags);
          putchar ('\n');
        }
    }
}

/* Handle a PE format file.  */

static void
dump_pe (bfd * abfd, struct external_PEI_filehdr * fhdr)
{
  unsigned short magic = bfd_h_get_16 (abfd, fhdr->e_magic);

  if (magic != IMAGE_DOS_SIGNATURE)
    {
      non_fatal ("not a PE format file - unexpected magic number");
      return;
    }
  
  if (options[OPT_FILE_HEADER].selected)
    dump_pe_file_header (abfd, fhdr);
  
  if (options[OPT_SECTIONS].selected)
    dump_pe_sections_header (abfd, fhdr);
}

/* Dump ABFD (according to the options[] array).  */

static void
pe_dump_obj (bfd *abfd)
{
  struct external_PEI_filehdr fhdr;

  /* Read file header.  */
  if (bfd_seek (abfd, 0, SEEK_SET) != 0
      || bfd_bread (& fhdr, sizeof (fhdr), abfd) != sizeof (fhdr))
    {
      non_fatal (_("cannot seek to/read file header"));
      return;
    }

  dump_pe (abfd, & fhdr);
}

/* Dump a PE file.  */

static void
pe_dump (bfd *abfd)
{
  /* We rely on BFD to decide if the file is a core file.  Note that core
     files are only supported on native environment by BFD.  */
  switch (bfd_get_format (abfd))
    {
    case bfd_core:
      break;
    default:
      pe_dump_obj (abfd);
      break;
    }
}

/* Vector for pe.  */

const struct objdump_private_desc objdump_private_desc_pe =
  {
    pe_help,
    pe_filter,
    pe_dump,
    options
  };
