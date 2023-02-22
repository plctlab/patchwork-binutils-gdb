#source: crc-iso.s
#ld: -T crc-iso.t
#objdump: -s -j .text
#notarget: [is_aout_format]
#xfail: tic4x-*-* tic54x-*-*

.*:     file format .*

Contents of section .text:
 1100 434f4445 deadbeef 00000000 000000a8  CODE............
 1110 10110000 00000000 10280000 00000000  .*
 1120 00170000 00000000 deadbeef 434f4445  ............CODE
 1130 434f4445 10110000 ffffffff ffffffff  CODE............
 1140 ffffffff ffffffff ffffffff ffffffff  .*
 1150 ffffffff ffffffff ffffffff ffffffff  .*
 1160 ffffffff ffffffff ffffffff ffffffff  .*
 1170 ffffffff ffffffff ffffffff ffffffff  .*
 1180 ffffffff ffffffff ffffffff ffffffff  .*
#...
 1f80 ffffffff ffffffff ffffffff ffffffff  .*
 1f90 ffffffff ffffffff ffffffff ffffffff  .*
 1fa0 ffffffff ffffffff ffffffff ffffffff  .*
 1fb0 ffffffff ffffffff ffffffff ffffffff  .*
 1fc0 ffffffff ffffffff ffffffff ffffffff  .*
 1fd0 ffffffff ffffffff ffffffff ffffffff  .*
 1fe0 ffffffff ffffffff ffffffff ffffffff  .*
 1ff0 ffffffff ffffffff 434f4445 deadbeef  ........CODE....
 2000 00000000 00000000 00000000 000000d8  .*
 2010 00000000 00000068 00000000 000000b0  .......h........
 2020 00000000 000000d0 00000000 00000008  .*
 2030 00000000 000000b8 00000000 00000060  ...............`
 2040 00000000 00000078 00000000 000000a0  .......x........
 2050 00000000 00000010 00000000 000000c8  .*
 2060 00000000 000000a8 00000000 00000070  ...............p
 2070 00000000 000000c0 00000000 00000018  .*
 2080 00000000 000000f0 00000000 00000028  .*
#...
 2780 00000000 00000058 00000000 00000080  .......X........
 2790 00000000 00000030 00000000 000000e8  .......0........
 27a0 00000000 00000088 00000000 00000050  ...............P
 27b0 00000000 000000e0 00000000 00000038  ...............8
 27c0 00000000 00000020 00000000 000000f8  ....... ........
 27d0 00000000 00000048 00000000 00000090  .......H........
 27e0 00000000 000000f0 00000000 00000028  .*
 27f0 00000000 00000098 00000000 00000040  ...............@
 2800 434f4445 deadbeef 00000000 00000000  CODE............
#pass
