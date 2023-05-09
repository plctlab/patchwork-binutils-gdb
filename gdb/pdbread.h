/* Include file for PDB debugging format support.
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

/* Header files referred to below can be found in Microsoft's PDB
   repository: https://github.com/microsoft/microsoft-pdb.  */

#ifndef PDBREAD_H
#define PDBREAD_H

#define PDB_TPI_STREAM_NUM	2

#define LF_FIELDLIST		0x1203
#define LF_INDEX		0x1404
#define LF_ENUMERATE		0x1502
#define LF_ENUM			0x1507
#define LF_CHAR			0x8000
#define LF_SHORT		0x8001
#define LF_USHORT		0x8002
#define LF_LONG			0x8003
#define LF_ULONG		0x8004
#define LF_QUADWORD		0x8009
#define LF_UQUADWORD		0x800a

#define T_CHAR			0x0010
#define T_UCHAR			0x0020
#define T_INT1			0x0068
#define T_UINT1			0x0069
#define T_SHORT			0x0011
#define T_USHORT		0x0021
#define T_INT2			0x0072
#define T_UINT2			0x0073
#define T_LONG			0x0012
#define T_ULONG			0x0022
#define T_INT4			0x0074
#define T_UINT4			0x0075
#define T_QUAD			0x0013
#define T_UQUAD			0x0023
#define T_INT8			0x0076
#define T_UINT8			0x0077

/* from bitfield structure CV_prop_t in cvinfo.h */
#define CV_PROP_FORWARD_REF	0x80

/* HDR in tpi.h */
struct pdb_tpi_stream_header
{
  uint32_t version;
  uint32_t header_size;
  uint32_t type_index_begin;
  uint32_t type_index_end;
  uint32_t type_record_bytes;
  uint16_t hash_stream_index;
  uint16_t hash_aux_stream_index;
  uint32_t hash_key_size;
  uint32_t num_hash_buckets;
  uint32_t hash_value_buffer_offset;
  uint32_t hash_value_buffer_length;
  uint32_t index_offset_buffer_offset;
  uint32_t index_offset_buffer_length;
  uint32_t hash_adj_buffer_offset;
  uint32_t hash_adj_buffer_length;
};

#define TPI_STREAM_VERSION_80		20040203

/* lfEnum in cvinfo.h */
struct lf_enum
{
  uint16_t kind;
  uint16_t num_elements;
  uint16_t properties;
  uint32_t underlying_type;
  uint32_t field_list;
} ATTRIBUTE_PACKED;

/* lfEnumerate in cvinfo.h */
struct lf_enumerate
{
  uint16_t attributes;
  uint16_t value;
} ATTRIBUTE_PACKED;

/* lfIndex in cvinfo.h */
struct lf_index
{
  uint16_t padding;
  uint32_t index;
} ATTRIBUTE_PACKED;

#endif /* PDBREAD_H */
