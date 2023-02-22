/* Linker command language support.
   Copyright (C) 1991-2023 Free Software Foundation, Inc.

   This file is part of the GNU Binutils.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#define	DEBUG_CRC	0

#include "sysdep.h"
#include "bfd.h"
#include "safe-ctype.h"
#include "obstack.h"
#include "bfdlink.h"
#include "ctf-api.h"

#include "ld.h"
#include "ldmain.h"
#include "ldexp.h"
#include "ldlang.h"
#include <ldgram.h>
#include "ldlex.h"
#include "ldmisc.h"
#include "lddigest.h"

/* CRC calculation on output section */
asection *text_section;
unsigned char *text_contents = NULL;

algo_t crc_algo = no_algo;
bfd_vma crc_size = 0;		/* Size of syndrome */
bool crc_invert = false;

bfd_vma crc64_poly = CRC_POLY_64;	/* Default Polynome is CRC64 ECMA */
bfd_vma *crc64_tab = NULL;

uint32_t crc32_poly = CRC_POLY_32;	/* Default Polynome is CRC-32 */
uint32_t *crc32_tab = NULL;

char *CRC_ADDRESS = NULL;
char *CRC_START = NULL;
char *CRC_END = NULL;
char *CRC_TABLE = NULL;

const char *digest_section = ".text";

/* ============ CRC-32 public functions ======================================*/

void
lang_add_crc32_syndrome (bool invert, bfd_vma poly)
{
  unsigned int poly32 = (unsigned int) (poly & 0xFFFFFFFF);
#if (DEBUG_CRC == 1)
  printf ("%s: invert=%d, poly=0x%08ul\n", __FUNCTION__, invert, poly32);
#endif
  if (crc_algo == no_algo)	/* We only allow one CRC64 <polynom> */
    {
      crc_algo = crc_algo_32;
      crc_size = sizeof (uint32_t);
      crc_invert = invert;
      crc32_poly = poly32;	/* Set the polynom */
      CRC_ADDRESS = CRC32_ADDRESS;
      CRC_START = CRC32_START;
      CRC_END = CRC32_END;
      CRC_TABLE = CRC32_TABLE;

#if (DEBUG_CRC == 1)
      printf ("Adding Syndrome: 0x%08lx\n", poly);
#endif
      lang_add_data (LONG, exp_intop (0));	/* Reserve room for the ECC value */
      crc32_tab = init_crc32_tab (crc32_poly);
      if (crc32_tab == NULL)
	{
	  einfo (_("%F%P: can not allocate memory for CRC table: %E\n"));
	  return;
	}
    }
  else
    {
      einfo (_("%P:%pS: warning: Only the first CRC polynome is used\n"),
	     NULL);
    }
}

void
lang_add_crc32_table (void)
{
  uint32_t *crc32_table = crc32_tab;	/* Use a precomputed, if it exists */
  bool local_table = false;
  if (crc32_table == NULL)
    {				/* No luck, create a table */
      crc32_table = init_crc32_tab (crc32_poly);
      if (crc32_table == NULL)
	{
	  einfo (_("%F%P: can not allocate memory for CRC table: %E\n"));
	  return;
	}
      local_table = true;
    }
  for (bfd_vma i = 0; i < 256; i++)
    {
      lang_add_data (LONG, exp_intop (crc32_table[i]));
    }
  if (local_table)
    free (crc32_table);
}

/* ============ CRC-64 public functions ======================================*/

void
lang_add_crc64_syndrome (bool invert, bfd_vma poly)
{
#if (DEBUG_CRC == 1)
  printf ("%s: invert=%d poly=0x%016lu\n", __FUNCTION__, invert, poly);
#endif
  if (crc_algo == no_algo)	/* We only allow one CRC64 <polynom> */
    {
      crc_algo = crc_algo_64;
      crc_size = sizeof (bfd_vma);
      crc_invert = invert;
      crc64_poly = poly;	/* Set the polynom */
      CRC_ADDRESS = CRC64_ADDRESS;
      CRC_START = CRC64_START;
      CRC_END = CRC64_END;
      CRC_TABLE = CRC64_TABLE;

#if (DEBUG_CRC == 1)
      printf ("Adding Syndrome: 0x%016lu\n", poly);
#endif
      lang_add_data (QUAD, exp_intop (0));	/* Reserve room for the ECC value */
      crc64_tab = init_crc64_tab (crc64_poly);
      if (crc64_tab == NULL)
	{
	  einfo (_("%F%P: can not allocate memory for CRC table: %E\n"));
	  return;
	}
    }
  else
    {
      einfo (_("%P:%pS: warning: Only the first CRC polynome is used\n"),
	     NULL);
    }
}

void
lang_add_crc64_table (void)
{
  bfd_vma *crc64_table = crc64_tab;	/* Use a precomputed, if it exists */
  bool local_table = false;
  if (crc64_table == NULL)
    {				/* No luck, create a table */
#if (DEBUG_CRC == 1)
      printf ("%s: Init CRC64 Tab\n", __FUNCTION__);
#endif
      crc64_table = init_crc64_tab (crc64_poly);
#if (DEBUG_CRC == 1)
      printf ("%s: Init CRC64 Tab DONE\n", __FUNCTION__);
#endif
      if (crc64_table == NULL)
	{
	  einfo (_("%F%P: can not allocate memory for CRC table: %E\n"));
	  return;
	}
      local_table = true;
    }
#if (DEBUG_CRC == 1)
  printf ("%s: Adding to table\n", __FUNCTION__);
#endif
  for (bfd_vma i = 0; i < 256; i++)
    {
      lang_add_data (QUAD, exp_intop (crc64_table[i]));
    }
  if (local_table)
    free (crc64_table);
}

/* ============ DIGEST COMMON functions ======================================*/

void
lang_add_digest (bool invert, bfd_vma size, bfd_vma poly)
{
  if (crc_algo != no_algo)	/* We only allow one CRC <polynom> */
    {
      einfo (_("%P:%pS: warning: Only the first CRC polynome is used\n"),
	     NULL);
      return;
    }

  if (size == 32)
    {
      lang_add_crc32_syndrome (invert, poly);
    }
  else if (size == 64)
    {
      lang_add_crc64_syndrome (invert, poly);
    }
  else
    {
      einfo (_("%F%P: Illegal Size in DIGEST: %E\n"));
      return;
    }
}

bool
lang_set_digest (char *digest)
{
#if (DEBUG_CRC == 1)
  printf ("%s: DIGEST=%s\n", __FUNCTION__, digest);
#endif
  if (crc_algo != no_algo)	/* We only allow one CRC <polynom> */
    {
      einfo (_("%P:%pS: warning: Only the first CRC polynome is used\n"),
	     NULL);
      return false;
    }

  if (!strcmp (digest, "CRC64-ECMA"))
    {
      lang_add_crc64_syndrome (false, CRC_POLY_64);
    }
  else if (!strcmp (digest, "CRC64-WE"))
    {
      lang_add_crc64_syndrome (true, CRC_POLY_64);
    }
  else if (!strcmp (digest, "CRC64-ISO"))
    {
      lang_add_crc64_syndrome (false, CRC_POLY_64_ISO);
    }
  else if (!strcmp (digest, "CRC32"))
    {
      lang_add_crc32_syndrome (true, CRC_POLY_32);
    }
  else
    {
      einfo (_("%F%P: Unknown DIGEST: %E\n"));
      return false;
    }
  return true;
}

void
lang_add_digest_table (void)
{
#if (DEBUG_CRC == 1)
  printf ("%s: size=%d\n", __FUNCTION__, (int) crc_algo);
#endif
  if (crc_algo == crc_algo_32)
    {
      lang_add_crc32_table ();
    }
  else if (crc_algo == crc_algo_64)
    {
      lang_add_crc64_table ();
    }
#if (DEBUG_CRC == 1)
  printf ("%s: END\n", __FUNCTION__);
#endif
}

void
lang_set_digest_section (char *section)
{
#if (DEBUG_CRC == 1)
  printf ("%s: size=%d\n", __FUNCTION__, (int) crc_algo);
#endif
  digest_section = section;
}

/* ============ Access functions for inserting checksum in text section=======*/
static bool
get_text_section_contents (void)
{
  /*
   * Get the '.text' section
   * Is there a risk that CRC needs to be calculated on more than .text?
   * We do not support that...
   */
  text_section =
    bfd_get_section_by_name (link_info.output_bfd, digest_section);
  if (text_section == NULL)
    {
      einfo (_("%P:%pS: Cannot retrieve '.text' section for CRC calc\n"),
	     NULL);
      return false;
    }

  /* Get the contents of the '.text' area so we can calculate the CRC */
  if (!bfd_malloc_and_get_section (link_info.output_bfd,
				   text_section->output_section,
				   (bfd_byte **) & text_contents))
    {
      einfo (_("%P:%pS: warning: '.text' section contents unavailable\n"
	       "CRC generation aborted\n"), NULL);
      return false;
    }

#if (DEBUG_CRC == 1)
  printf ("%s: [0x%08lx .. 0x%08lx]\n",
	  text_section->name,
	  text_section->lma, text_section->lma + text_section->size - 1);
#endif
  return true;
}

/* Set variable in the '.text' area */
static bool
set_crc_checksum (bfd_vma crc, bfd_vma addr, bfd_vma size)
{
  if (!bfd_set_section_contents (link_info.output_bfd,
				 text_section->output_section,
				 &crc, addr, size))
    {
      einfo (_("%P:%pS: warning: updating CRC failed\n"
	       "CRC generation aborted\n"), NULL);
      return false;
    }
  return true;
}

static bool
symbol_lookup (char *name, bfd_vma * val)
{
  struct bfd_link_hash_entry *h;
  *val = 0ull;
  h = bfd_link_hash_lookup (link_info.hash, name, false, false, true);
  if (h != NULL)
    {
      if (((h->type == bfd_link_hash_defined) ||
	   (h->type == bfd_link_hash_defweak)) &&
	  (h->u.def.section->output_section != NULL))
	{
	  *val = (h->u.def.value
		  + bfd_section_vma (h->u.def.section->output_section)
		  + h->u.def.section->output_offset);
	  return true;
	}
    }
  return false;
}

/* ============ CRC DEBUG functions ==========================================*/

#if (DEBUG_CRC == 1)
static void
debug_hex (char *prompt, unsigned char *section, bfd_vma address, bfd_vma sz)
{
  bfd_vma *vma_section = (bfd_vma *) section;
  bfd_vma size = (sz) / sizeof (bfd_vma);
  printf ("%s:\n", prompt);
  for (bfd_vma i = 0; i < size; i += 8)
    {
      printf ("0x%08lx: 0x%016lx 0x%016lx 0x%016lx 0x%016lx\n",
	      address + (i * sizeof (bfd_vma)),
	      vma_section[i + 0],
	      vma_section[i + 1], vma_section[i + 2], vma_section[i + 3]);
    }
}

static void
debug_crc_header (char *prompt)
{
  debug_hex (prompt, text_contents, text_section->vma, 64);
}

static void
debug_crc_update (bfd_vma crc, bfd_vma crc_addr)
{
  printf ("CRC [0x%016lx] update at 0x%08lx succeeded\n", crc, crc_addr);
}

static void
debug_full_textsection (void)
{

  /* In order to see the updated content, we have to fetch it again */

  if (!get_text_section_contents ())
    {
      debug_crc_header ("After CRC");
      debug_hex ("Full Section After CRC",
		 text_contents, text_section->vma, text_section->size);
      free (text_contents);
    }
}
#else
#define	debug_hex(p,s,a,sz)
#define debug_crc_header(p)
#define debug_crc_update(c, a)
#define debug_full_textsection()
#endif

/* ============ CRC common functions =========================================*/
/*
 * Multiplexing function for calculating CRC with different algorithms
 * 'crc_algo'
 */
static bfd_vma
calculate_crc (const unsigned char *input_str, size_t num_bytes)
{
  if (crc_algo == crc_algo_64)
    {
      if (crc64_tab != NULL)
	{
	  return calc_crc64 (input_str, num_bytes);
	}
    }
  else if (crc_algo == crc_algo_32)
    {
      if (crc32_tab != NULL)
	{
	  return calc_crc32 (input_str, num_bytes);
	}
    }
  /* This should never happen */
  return 0;
}

static bool
invalid_crc_parameters (bfd_vma crc_addr,
			bfd_vma crc_area_start, bfd_vma crc_area_end)
{
  bool crc_in_section;
  /* Get limits of '.text' section */
  bfd_vma text_start = text_section->lma;
  bfd_vma text_end = text_section->lma + text_section->size;

  /* All three symbols must be inside the '.text' section */
  crc_in_section =
    ((text_start <= crc_addr) && (crc_addr <= text_end)) &&
    ((text_start <= crc_area_start) && (crc_area_start <= text_end)) &&
    ((text_start <= crc_area_end) && (crc_area_end <= text_end));

  if (!crc_in_section)
    {
      einfo (_("%P:%pS: warning: CRC area outside the '.text' section\n"
	       "CRC generation aborted\n"), NULL);
      /*
       * Maybe we should printout the text section start and end
       * as well as the boundaries of the CRC check area.
       */
      return true;
    }

  /*
   * CRC checksum must be outside the checked area
   * We must check that they do not overlap in the beginning
   */
  {
    bool crc_valid = false;
    if (crc_addr < crc_area_start)
      {
	if ((crc_addr + crc_size) <= crc_area_start)
	  {
	    crc_valid = true;
	  }
      }
    else if (crc_addr >= crc_area_end)
      {
	crc_valid = true;
      }
    if (!crc_valid)
      {
	einfo (_("%P:%pS: warning: CRC located inside checked area\n"
		 "CRC generation aborted\n"), NULL);
	return true;
      }
  }
  return false;
}

void
lang_generate_crc (void)
{
#if (DEBUG_CRC == 1)
  printf ("%s\n", __FUNCTION__);
#endif
  bfd_vma crc_addr, crc_area_start, crc_area_end;
  bfd_vma crc;
  bool can_do_crc;

  /* Return immediately, if CRC is not requested */
  if (crc_algo == no_algo)
    return;

  if (!get_text_section_contents ())
    {
      /* Error messages inside check */
      return;
    }
  /*
   * These symbols must be present, for CRC to be generated
   * They should all have been defined in a CRC## <syndrome> statement
   * If they are not defined, then there is an internal error.
   * Should we consider using symbols which cannot be parsed by the linker?
   * I.E. CRC-64 is never an identifier
   */
  can_do_crc = symbol_lookup (CRC_ADDRESS, &crc_addr) &&
    symbol_lookup (CRC_START, &crc_area_start) &&
    symbol_lookup (CRC_END, &crc_area_end);

  if (!can_do_crc)
    {
      einfo (_("%P:%pS: Internal Error - __CRC#___ symbols not defined\n"
	       "CRC generation aborted\n"), NULL);
      return;
    }

  /* Check that the addresses make sense */
  if (invalid_crc_parameters (crc_addr, crc_area_start, crc_area_end))
    {
      /* Error messages inside check */
      return;
    }

  /* Calculate and set the CRC */
  {
    /*
     * The '.text' area does not neccessarily start at 0x00000000,
     * so we have to shift the indices.
     */
    bfd_vma _crc_addr = crc_addr - text_section->vma;
    bfd_vma _crc_area_start = crc_area_start - text_section->vma;
    bfd_vma _crc_area_end = crc_area_end - text_section->vma;


    /* This is the CRC calculation which we worked so hard for */
    debug_crc_header ("Before CRC");
    crc = calculate_crc (&text_contents[_crc_area_start],
			 _crc_area_end - _crc_area_start);


    /*
     * The contents of the '.text' section are no longer needed.
     * It is a copy of the section contents, and will therefore be stale
     * after we updated the section with the CRC checksum.
     * Remove it before we set the CRC checksum, to simplify the code logic.
     */
    free (text_contents);
    if (set_crc_checksum (crc, _crc_addr, crc_size))
      {
	debug_crc_update (crc, crc_addr);
      }
  }

  debug_full_textsection ();
}

/* ============ END CRC common functions =====================================*/

void
lang_generate_digest (void)
{
  /* Return immediately, if CRC is not requested */
  if (crc_algo == no_algo)
    return;

  /* Handle 32/64-bit CRCs */
  if ((crc_algo == crc_algo_32) || (crc_algo == crc_algo_32))
    {
      lang_generate_crc ();
    }
}
