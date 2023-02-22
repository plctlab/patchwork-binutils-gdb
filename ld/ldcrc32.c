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

/* ============ CRC-32 LIBCRC functions ======================================*/

/*
 * void init_crc32_tab( void );
 *
 * For optimal speed, the CRC32 calculation uses a table with pre-calculated
 * bit patterns which are used in the XOR operations in the program.
 * init_crc32_tab is copyright (c) 2016 Lammert Bies
 */
uint32_t *
init_crc32_tab (uint32_t poly)
{
  uint32_t i;
  uint32_t j;
  uint32_t crc;
  uint32_t *crc_tab;

  crc_tab = malloc (256 * sizeof (uint32_t));
  if (crc_tab == NULL)
    return NULL;

  for (i = 0; i < 256; i++)
    {

      crc = i;

      for (j = 0; j < 8; j++)
	{

	  if (crc & 0x00000001L)
	    {
	      crc = (crc >> 1) ^ poly;
	    }
	  else
	    {
	      crc = crc >> 1;
	    }
	}

      crc_tab[i] = crc;
    }
  return crc_tab;
}				/* init_crc32_tab */

/*
 * uint32_t calc_crc32_inv( const unsigned char *input_str, size_t num_bytes );
 *
 * The function calc_crc32_inv() calculates in one pass the common 32 bit CRC value for
 * a byte string that is passed to the function together with a parameter
 * indicating the length.
 */

uint32_t
calc_crc32_inv (const unsigned char *input_str, size_t num_bytes)
{
  uint32_t crc;
  const unsigned char *ptr;
  size_t a;

  crc = CRC_START_32_INV;
  ptr = input_str;

  if (ptr != NULL)
    {
      for (a = 0; a < num_bytes; a++)
	{
	  crc = (crc >> 8) ^
	    crc32_tab[(crc ^ (uint32_t) * ptr++) & 0x000000FFul];
	}
    }

  return (crc ^ 0xFFFFFFFFul);

}				/* calc_crc32_inv */

/*
 * uint32_t calc_crc32( const unsigned char *input_str, size_t num_bytes );
 *
 * The function calc_crc32() calculates in one pass the common 32 bit CRC value for
 * a byte string that is passed to the function together with a parameter
 * indicating the length.
 */
uint32_t
calc_crc32 (const unsigned char *input_str, size_t num_bytes)
{
  uint32_t crc;
  const unsigned char *ptr;
  size_t a;
  if (crc_invert)
    return calc_crc32_inv (input_str, num_bytes);

  crc = 0;
  ptr = input_str;

  if (ptr != NULL)
    {
      for (a = 0; a < num_bytes; a++)
	{
	  crc = (crc >> 8) ^
	    crc32_tab[(crc ^ (uint32_t) * ptr++) & 0x000000FFul];
	}
    }

  return (crc);

}				/* calc_crc32 */
