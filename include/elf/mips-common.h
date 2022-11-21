/* MIPS ELF support for BFD.
   Copyright (C) 2018-2022 Free Software Foundation, Inc.

   This file is part of BFD, the Binary File Descriptor library.

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

/* This file holds definitions common to the MIPS and nanoMIPS ELF ABIs.  */

#ifndef _ELF_MIPS_COMMON_H
#define _ELF_MIPS_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/* Values for the xxx_size bytes of an ABI flags structure.  */

#define AFL_REG_NONE	     0x00	/* No registers.  */
#define AFL_REG_32	     0x01	/* 32-bit registers.  */
#define AFL_REG_64	     0x02	/* 64-bit registers.  */
#define AFL_REG_128	     0x03	/* 128-bit registers.  */

#ifdef __cplusplus
}
#endif

#endif /* _ELF_MIPS_COMMON_H */
