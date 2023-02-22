/*
 * Library: libcrc
 * Author:  Lammert Bies
 *
 * This file is licensed under the MIT License as stated below
 *
 * Copyright (c) 2016 Lammert Bies
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "sysdep.h"
#include "bfd.h"
#include "lddigest.h"

/* ============ CRC-64 LIBCRC functions ======================================*/

/*
 * bfd_vma *init_crc64_tab( bfd_vma poly ) ;
 *
 * For optimal speed, the CRC64 calculation uses a table with pre-calculated
 * bit patterns which are used in the XOR operations in the program.
 * init_crc64_tab is copyright (c) 2016 Lammert Bies
 */
bfd_vma *
init_crc64_tab (bfd_vma poly)
{
  bfd_vma i;
  bfd_vma j;
  bfd_vma c;
  bfd_vma crc;
  bfd_vma *crc_tab;

  crc_tab = malloc (256 * sizeof (bfd_vma));
  if (crc_tab == NULL)
    return NULL;

  for (i = 0; i < 256; i++)
    {
      crc = 0;
      c = i << 56;
      for (j = 0; j < 8; j++)
	{
	  if ((crc ^ c) & 0x8000000000000000ull)
	    crc = (crc << 1) ^ poly;
	  else
	    crc = crc << 1;
	  c = c << 1;
	}
      crc_tab[i] = crc;
    }
  return crc_tab;

}				/* init_crc64_tab */

/*
 * The function calc_crc64_inv() calculates in one pass the CRC64 64 bit CRC
 * value for a byte string that is passed to the function together with a
 * parameter indicating the length.
 * This is used for CRC64-WE
 * calc_crc64_inv is copyright (c) 2016 Lammert Bies
 */
bfd_vma
calc_crc64_inv (const unsigned char *input_str, size_t num_bytes)
{
  bfd_vma crc;
  const unsigned char *ptr;
  size_t a;

  crc = CRC_START_64_INV;
  ptr = input_str;

  if (ptr != NULL)
    {
      for (a = 0; a < num_bytes; a++)
	{
	  crc = (crc << 8) ^
	    crc64_tab[((crc >> 56) ^ (bfd_vma) * ptr++) &
		      0x00000000000000FFull];
	}
    }
  return crc ^ 0xFFFFFFFFFFFFFFFFull;
}				/* calc_crc64_inv */

/*
 * bfd_vma calc_crc64( const unsigned char *input_str, size_t num_bytes );
 *
 * The function calc_crc64() calculates in one pass the 64 bit CRC value
 * for a byte string that is passed to the function together with a
 * parameter indicating the length.
 * This is used for CRC64-ECMA and CRC64-ISO
 * calc_crc64 is copyright (c) 2016 Lammert Bies
 */
bfd_vma
calc_crc64 (const unsigned char *input_str, size_t num_bytes)
{
  bfd_vma crc;
  const unsigned char *ptr;
  size_t a;
  if (crc_invert)
    return calc_crc64_inv (input_str, num_bytes);
  crc = CRC_START_64;
  ptr = input_str;
  if (ptr != NULL)
    {
      for (a = 0; a < num_bytes; a++)
	{
	  crc = (crc << 8) ^
	    crc64_tab[((crc >> 56) ^ (bfd_vma) * ptr++) &
		      0x00000000000000FFull];
	}
    }
  return crc;
}				/* calc_crc64 */
