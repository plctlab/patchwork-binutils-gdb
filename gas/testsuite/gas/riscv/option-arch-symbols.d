#as: -misa-spec=2.2
#source: option-arch.s
#objdump: --syms --special-syms

.*file format.*riscv.*

SYMBOL TABLE:
#...
0+00 l       .text	0000000000000000 \$xrv64i2p0_c2p0
0+02 l       .text	0000000000000000 \$xrv64i2p0_f2p0_d2p0_xvendor1p0
0+0a l       .text	0000000000000000 \$xrv64i2p0_m3p0_f2p0_d2p0_zmmul1p0_xvendor1p0_xvendor32x3p0
0+0e l       .text	0000000000000000 \$xrv32i2p1_c2p0
#...
