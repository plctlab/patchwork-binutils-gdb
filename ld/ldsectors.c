/* Linker command language support.
   Copyright (C) 1991-2023 Ulf Samuelsson <ulf@emagii.com>

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

#define _GNU_SOURCE
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

typedef struct
{
  const char *name;
  int count;
  int location;
} bank_t;

typedef struct symbol
{
  uint64_t value;
  char *str;
} symbol_t;

typedef struct sector
{
  symbol_t begin;
  symbol_t end;
  symbol_t size;
  const char *name;
} sector_t;

typedef struct list list_t;
struct list
{
  list_t *next;
  void *data;
};

typedef struct
{
  list_t *first;
  list_t *last;
  char *name;
} head_t;

bank_t dummy_bank = {.name = "dummy",.count = 0 };
list_t dummy_bank_l = {.next = NULL,.data = (void *) &dummy_bank };
head_t banks = { &dummy_bank_l, &dummy_bank_l, "banks" };

sector_t dummy_sector = {
  .begin = {0, NULL},
  .end = {0, NULL},
  .size = {0, NULL},
  .name = NULL
};
list_t dummy_sector_l = {.next = NULL,.data = (void *) &dummy_sector };
head_t sectors = { &dummy_sector_l, &dummy_sector_l, "sectors" };

#if 0
static void
print_symbol (symbol_t * s)
{
  if (s != NULL)
    {
      printf ("%-32s= 0x%016lx;\n", s->str, s->value);
    }
}

static void
print_sector (sector_t * s)
{
  print_symbol (&s->begin);
  print_symbol (&s->end);
  print_symbol (&s->size);
}
#endif

static list_t *
list_add_to_end (head_t * h, void *element)
{
  list_t *e = (list_t *) malloc (sizeof (list_t));
  if (e != NULL)
    {
      e->next = NULL;
      e->data = element;
      if (h->first == NULL)
	{
	  h->first = e;
	}
      h->last->next = (void *) e;
      h->last = (void *) e;
    }
  return e;
}

void
lang_add_bank (const char *name)
{
  bank_t *b = malloc (sizeof (bank_t));
  list_t *l;
  if (b == NULL)
    {
      einfo (_("%F%P: can not allocate memory for memory bank list: %E\n"));
      return;
    }
  b->name = name;
  b->count = 0;
  l = list_add_to_end (&banks, (void *) b);
  if (l == NULL)
    {
      einfo (_("%F%P: can not allocate memory for memory bank: %E\n"));
    }
}

void
lang_add_sector (const char *size)
{
  char *p, c;
  bank_t *b;
  uint64_t val = strtoull (size, &p, 10);
  if (errno == ERANGE)
    return;
  /* Skip whitespace */
  while ((c = *p) != 0)
    {
      if (c <= ' ')
	{
	  p++;
	}
      else
	{
	  break;
	}
    }

  /* Translate to upper case */
  {
    char *tmpp = p;

    while ((c = *tmpp) != 0)
      {
	if ((c >= 'a') && (c <= 'z'))
	  {
	    c = c - 'a' + 'A';
	    *tmpp = c;
	  }
	tmpp++;
      }
  }

  /* check for multipliers */
  if (!strcmp (p, "BYTES"))
    {
      val *= 1;
    }
  else if (!strcmp (p, "KB"))
    {
      val *= 1024;
    }
  else if (!strcmp (p, "MB"))
    {
      val *= 1024 * 1024;
    }

  /* Create a sector record - unless dummy sector */
  b = banks.last->data;
  if (strncmp (b->name, "dummy", 5))
    {
      size_t len;
      list_t *l;
      sector_t *s = malloc (sizeof (sector_t));
      if (s == NULL)
	{
	  einfo (_("%F%P: can not allocate memory for sector list: %E\n"));
	  return;
	}

      s->begin.value = b->location;
      len = asprintf (&s->begin.str, "%s#%02d#begin", b->name, b->count);
      s->end.value = b->location + val;
      len += asprintf (&s->end.str, "%s#%02d#end", b->name, b->count);
      s->size.value = val;
      len += asprintf (&s->size.str, "%s#%02d#size", b->name, b->count);
      if (len <= 1)
	{
	};			/* 'Use' "len" to avoid warnings */
      l = list_add_to_end (&sectors, (void *) s);
      if (l == NULL)
	{
	  einfo (_("%F%P: can not allocate memory for sector: %E\n"));
	}
    }
  b->location += val;
  b->count++;
}

static etree_type *
dot (void)
{
  return exp_nameop (NAME, ".");
}

static etree_type *
begin_s (sector_t * s)
{
  return exp_nameop (NAME, s->begin.str);
}

static etree_type *
end_s (sector_t * s)
{
  return exp_nameop (NAME, s->end.str);
}

static etree_type *
size_s (sector_t * s)
{
  return exp_nameop (NAME, s->size.str);
}

static void
define_symbol (symbol_t * symbol)
{
  etree_type *value = exp_bigintop ((bfd_vma) symbol->value, NULL);
  lang_add_assignment (exp_assign (symbol->str, value, true));
}

static void
define_sector (sector_t * s)
{
  define_symbol (&s->begin);
  define_symbol (&s->end);
  define_symbol (&s->size);
}

static bool
define_sectors (void)
{
  sector_t *s;
  bool present = false;
  for (list_t * sl = sectors.first->next; sl != NULL; sl = sl->next)
    {
      s = (sector_t *) sl->data;
      define_sector (s);
      present = true;
    }
  return present;
}

static void
cond_align_to_sector (sector_t * s)
{
  /*
   * Align, if location is within the sector
   * . = ( (. <= begin) && (. <= end) ) ? ALIGN(size) : . ;
   */
  etree_type *lower = exp_binop (GE, dot (), begin_s (s));
  etree_type *upper = exp_binop (LE, dot (), end_s (s));
  etree_type *in_range = exp_binop (ANDAND, lower, upper);
  etree_type *align = exp_unop (ALIGN_K, size_s (s));
  etree_type *expr = exp_trinop ('?', in_range, align, dot ());
  lang_add_assignment (exp_assign (".", expr, false));
}

void
lang_align_sector (void)
{
  static bool defined = false;
  if (!defined)
    {
      defined = define_sectors ();
    }
  if (!defined)
    {
      einfo (_("%F%P: 'ALIGN_SECTOR' needs to be preceeded by a"
	       " 'BANK' command\n"));
    }
  for (list_t * sl = sectors.first->next; sl != NULL; sl = sl->next)
    {
      cond_align_to_sector ((sector_t *) sl->data);
    }
}
