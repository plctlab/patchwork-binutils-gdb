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

#ifndef CHECKSUM_H
#define CHECKSUM_H

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

enum crc_alg {
  crc_algo_none=0,
  crc_algo_32=4,
  crc_algo_64=8
};

bfd_vma	crc_64    (const unsigned char *input_str, size_t num_bytes);
bfd_vma	crc_64_inv(const unsigned char *input_str, size_t num_bytes);

#endif /* CHECKSUM_H */
