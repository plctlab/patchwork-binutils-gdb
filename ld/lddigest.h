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

#ifndef LDDIGEST_H
#define LDDIGEST_H

#include <stddef.h>
#include <stdint.h>

#define	CRC_POLY_64		0x42F0E1EBA9EA3693ull
#define	CRC_POLY_64_ISO		0xD800000000000000ull
#define	CRC_START_64		0x0000000000000000ull
#define	CRC_START_64_INV	0xFFFFFFFFFFFFFFFFull

#define	CRC64_ADDRESS		"___CRC64___"
#define	CRC64_START		"___CRC64_START___"
#define	CRC64_END		"___CRC64_END___"
#define	CRC64_TABLE		"___CRC64_TABLE___"

#define	CRC_POLY_32		0xEDB88320ul
#define	CRC_START_32_INV	0xFFFFFFFFul

#define	CRC32_ADDRESS		"___CRC32___"
#define	CRC32_START		"___CRC32_START___"
#define	CRC32_END		"___CRC32_END___"
#define	CRC32_TABLE		"___CRC32_TABLE___"

typedef enum algorithm
{
  no_algo = 0,
  sha_algo_1 = 1,
  crc_algo_32 = 4,
  crc_algo_64 = 8,
  sha_algo_256 = 256,
  sha_algo_512
} algo_t;



extern char *CRC_ADDRESS;
extern char *CRC_START;
extern char *CRC_END;
extern char *CRC_TABLE;
extern uint32_t *crc32_tab;
extern bfd_vma *crc64_tab;
extern bool crc_invert;

extern void lang_add_crc32_syndrome (bool invert, bfd_vma poly);
extern void lang_add_crc32_table (void);
extern void lang_add_crc64_syndrome (bool invert, bfd_vma poly);
extern void lang_add_crc64_table (void);

extern void lang_add_digest (bool invert, bfd_vma size, bfd_vma polynome);
extern bool lang_set_digest (char *digest);
extern void lang_add_digest_table (void);
extern void lang_generate_crc (void);
extern void lang_generate_digest (void);
extern void lang_set_digest_section (char *section);

/* CRC-32 */
extern uint32_t *init_crc32_tab (uint32_t poly);
extern uint32_t calc_crc32_inv
  (const unsigned char *input_str, size_t num_bytes);
extern uint32_t calc_crc32 (const unsigned char *input_str, size_t num_bytes);

/* CR-64 */
extern bfd_vma *init_crc64_tab (bfd_vma poly);
extern bfd_vma calc_crc64_inv
  (const unsigned char *input_str, size_t num_bytes);
extern bfd_vma calc_crc64 (const unsigned char *input_str, size_t num_bytes);

#endif /* LDDIGEST_H */
