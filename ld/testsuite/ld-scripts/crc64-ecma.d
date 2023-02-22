#source: crc-ecma.s
#ld: -T crc-ecma.t
#objdump: -s -j .text
#notarget: [is_aout_format]
#xfail: tic4x-*-* tic54x-*-*

.*:     file format .*

Contents of section .text:
 1100 434f4445 deadbeef d89e4425 b46db823  CODE......D%.m.#
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
 2000 00000000 00000000 9336eaa9 ebe1f042  .........6.....B
 2010 266dd453 d7c3e185 b55b3efa 3c2211c7  &m.S.....[>.<"..
 2020 dfec420e 45663349 4cdaa8a7 ae87c30b  ..B.Ef3IL.......
 2030 f981965d 92a5d2cc 6ab77cf4 7944228e  ...]....j.|.yD".
 2040 bed9851c 8acc6692 2def6fb5 612d96d0  ......f.-.o.a-..
 2050 98b4514f 5d0f8717 0b82bbe6 b6ee7755  ..QO].........wU
 2060 6135c712 cfaa55db f2032dbb 244ba599  a5....U...-.$K..
 2070 47581341 1869b45e d46ef9e8 f388441c  GX.A.i.^.n....D.
 2080 ef85e190 ff783d66 7cb30b39 1499cd24  .....x=f|..9...$
#...
 2780 d3db7c26 d56eb886 40ed968f 3e8f48c4  ..|&.n..@...>.H.
 2790 f5b6a875 02ad5903 668042dc e94ca941  ...u..Y.f.B..L.A
 27a0 0c373e28 90088bcf 9f01d481 7be97b8d  .7>.........{.{.
 27b0 2a5aea7b 47cb6a4a b96c00d2 ac2a9a08  *Z.{G.jJ.l...*..
 27c0 6d02f93a 5fa2de14 fe341393 b4432e56  m..:_....4...C.V
 27d0 4b6f2d69 88613f91 d859c7c0 6380cfd3  Ko-i.a?..Y..c...
 27e0 b2eebb34 1ac4ed5d 21d8519d f1251d1f  ...4...]!.Q..%..
 27f0 94836f67 cd070cd8 07b585ce 26e6fc9a  ..og........&...
 2800 434f4445 deadbeef 00000000 00000000  CODE............
#pass
