#source: crc32-poly.s
#ld: -T crc32-poly.t
#objdump: -s -j .text
#notarget: [is_aout_format]
#xfail: tic4x-*-* tic54x-*-*

.*:     file format .*

Contents of section .text:
 1100 434f4445 deadbeef 712c8793 0c110000  CODE....q,......
 1110 10240000 04130000 deadbeef 434f4445  .$..........CODE
 1120 434f4445 0c110000 ffffffff ffffffff  CODE............
 1130 ffffffff ffffffff ffffffff ffffffff  .*
 1140 ffffffff ffffffff ffffffff ffffffff  .*
 1150 ffffffff ffffffff ffffffff ffffffff  .*
 1160 ffffffff ffffffff ffffffff ffffffff  .*
 1170 ffffffff ffffffff ffffffff ffffffff  .*
 1180 ffffffff ffffffff ffffffff ffffffff  .*
#...
 1f90 ffffffff ffffffff ffffffff ffffffff  .*
 1fa0 ffffffff ffffffff ffffffff ffffffff  .*
 1fb0 ffffffff ffffffff ffffffff ffffffff  .*
 1fc0 ffffffff ffffffff ffffffff ffffffff  .*
 1fd0 ffffffff ffffffff ffffffff ffffffff  .*
 1fe0 ffffffff ffffffff ffffffff ffffffff  .*
 1ff0 ffffffff ffffffff 434f4445 deadbeef  ........CODE....
 2000 00000000 d23cc1eb 7b04d96a a9381881  .....<..{..j.8..
 2010 f608b2d5 2434733e 8d0c6bbf 5f30aa54  ....$4s>..k._0.T
 2020 336c3f16 e150fefd 4868e67c 9a542797  3l?..P..Hh.|.T'.
 2030 c5648dc3 17584c28 be6054a9 6c5c9542  .d...XL..`T.l\.B
 2040 66d87e2c b4e4bfc7 1ddca746 cfe066ad  f.~,.......F..f.
 2050 90d0ccf9 42ec0d12 ebd41593 39e8d478  ....B.......9..x
 2060 55b4413a 878880d1 2eb09850 fc8c59bb  U.A:.......P..Y.
 2070 a3bcf3ef 71803204 d8b82a85 0a84eb6e  ....q.2...*....n
 2080 ccb0fd58 1e8c3cb3 b7b42432 6588e5d9  ...X..<...$2e...
#...
 2380 bb6fab37 69536adc c06b725d 1257b3b6  .o.7iSj..kr].W..
 2390 4d6719e2 9f5bd809 3663c088 e45f0163  Mg...[..6c..._.c
 23a0 88039421 5a3f55ca f3074d4b 213b8ca0  ...!Z?U...MK!;..
 23b0 7e0b26f4 ac37e71f 050fff9e d7333e75  ~.&..7.......3>u
 23c0 ddb7d51b 0f8b14f0 a6b30c71 748fcd9a  ...........qt...
 23d0 2bbf67ce f983a625 50bbbea4 82877f4f  +.g....%P......O
 23e0 eedbea0d 3ce72be6 95df3367 47e3f28c  ....<.+...3gG...
 23f0 18d358d8 caef9933 63d781b2 b1eb4059  ..X....3c.....@Y
 2400 434f4445 deadbeef 00000000 00000000  CODE............
#pass
