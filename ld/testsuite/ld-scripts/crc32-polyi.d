#source: crc32-polyi.s
#ld: -T crc32-polyi.t
#objdump: -s -j .text
#notarget: [is_aout_format]
#xfail: tic4x-*-* tic54x-*-*

.*:     file format .*

Contents of section .text:
 1100 434f4445 deadbeef 8d51a265 0c110000  CODE.....Q.e....
 1110 10240000 04130000 deadbeef 434f4445  .$..........CODE
 1120 434f4445 0c110000 ffffffff ffffffff  CODE............
 1130 ffffffff ffffffff ffffffff ffffffff  .*
 1140 ffffffff ffffffff ffffffff ffffffff  .*
 1150 ffffffff ffffffff ffffffff ffffffff  .*
 1160 ffffffff ffffffff ffffffff ffffffff  .*
 1170 ffffffff ffffffff ffffffff ffffffff  .*
#...
 1f80 ffffffff ffffffff ffffffff ffffffff  .*
 1f90 ffffffff ffffffff ffffffff ffffffff  .*
 1fa0 ffffffff ffffffff ffffffff ffffffff  .*
 1fb0 ffffffff ffffffff ffffffff ffffffff  .*
 1fc0 ffffffff ffffffff ffffffff ffffffff  .*
 1fd0 ffffffff ffffffff ffffffff ffffffff  .*
 1fe0 ffffffff ffffffff ffffffff ffffffff  .*
 1ff0 ffffffff ffffffff 434f4445 deadbeef  ........CODE....
 2000 00000000 96300777 2c610eee ba510999  .....0.w,a...Q..
 2010 19c46d07 8ff46a70 35a563e9 a395649e  ..m...jp5.c...d.
 2020 3288db0e a4b8dc79 1ee9d5e0 88d9d297  2......y........
 2030 2b4cb609 bd7cb17e 072db8e7 911dbf90  +L...|.~.-......
 2040 6410b71d f220b06a 4871b9f3 de41be84  d.... .jHq...A..
 2050 7dd4da1a ebe4dd6d 51b5d4f4 c785d383  }......mQ.......
 2060 56986c13 c0a86b64 7af962fd ecc9658a  V.l...kdz.b...e.
 2070 4f5c0114 d96c0663 633d0ffa f50d088d  O\...l.cc=......
 2080 c8206e3b 5e10694c e44160d5 727167a2  . n;^.iL.A`.rqg.
#...
 2390 612667a7 f71660d0 4d476949 db776e3e  a&g...`.MGiI.wn>
 23a0 4a6ad1ae dc5ad6d9 660bdf40 f03bd837  Jj...Z..f..@.;.7
 23b0 53aebca9 c59ebbde 7fcfb247 e9ffb530  S..........G...0
 23c0 1cf2bdbd 8ac2baca 3093b353 a6a3b424  ........0..S...$
 23d0 0536d0ba 9306d7cd 2957de54 bf67d923  .6......)W.T.g.#
 23e0 2e7a66b3 b84a61c4 021b685d 942b6f2a  .zf..Ja...h].+o*
 23f0 37be0bb4 a18e0cc3 1bdf055a 8def022d  7..........Z...-
 2400 434f4445 deadbeef 00000000 00000000  CODE............
 #pass
