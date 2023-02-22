#source: crc-polyi.s
#ld: -T crc-polyi.t
#objdump: -s -j .text
#notarget: [is_aout_format]
#xfail: tic4x-*-* tic54x-*-*

.*:     file format .*

Contents of section .text:
 1100 434f4445 deadbeef b7f7857f d0d5802a  CODE...........*
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
 2000 00000000 00000000 efbeadde efbeadde  .*
 2010 31c3f663 30c3f663 de7d5bbd df7d5bbd  1..c0..c.}[..}[.
 2020 6286edc7 6086edc7 8d384019 8f384019  b...`....8@..8@.
 2030 53451ba4 50451ba4 bcfbb67a bffbb67a  SE..PE.....z...z
 2040 2bb27651 2eb27651 c40cdb8f c10cdb8f  +.vQ..vQ........
 2050 1a718032 1e718032 f5cf2dec f1cf2dec  .q.2.q.2..-...-.
 2060 49349b96 4e349b96 a68a3648 a18a3648  I4..N4....6H..6H
 2070 78f76df5 7ef76df5 9749c02b 9149c02b  x.m.~.m..I.+.I.+
 2080 5664eda2 5c64eda2 b9da407c b3da407c  Vd..\d....@|..@|
#...
 2780 415af2df 225af2df aee45f01 cde45f01  AZ.."Z...._..._.
 2790 709904bc 129904bc 9f27a962 fd27a962  p........'.b.'.b
 27a0 23dc1f18 42dc1f18 cc62b2c6 ad62b2c6  #...B....b...b..
 27b0 121fe97b 721fe97b fda144a5 9da144a5  ...{r..{..D...D.
 27c0 6ae8848e 0ce8848e 85562950 e3562950  j........V)P.V)P
 27d0 5b2b72ed 3c2b72ed b495df33 d395df33  [+r.<+r....3...3
 27e0 086e6949 6c6e6949 e7d0c497 83d0c497  .niIlniI........
 27f0 39ad9f2a 5cad9f2a d61332f4 b31332f4  9..*\..*..2...2.
 2800 434f4445 deadbeef 00000000 00000000  CODE............
 #pass
