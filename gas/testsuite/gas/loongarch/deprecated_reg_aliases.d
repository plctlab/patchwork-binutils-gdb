#name: Deprecated register aliases
#as-new:
#objdump: -d
#warning_output: deprecated_reg_aliases.l

.*:[ 	]+file format .*


Disassembly of section .text:

0000000000000000 <foo>:
[ 	]+0:[ 	]+14acf125[ 	]+lu12i\.w[ 	]+\$a1, 354185\(0x56789\)
[ 	]+4:[ 	]+038048a5[ 	]+ori[ 	]+\$a1, \$a1, 0x12
[ 	]+8:[ 	]+16024685[ 	]+lu32i\.d[ 	]+\$a1, 4660\(0x1234\)
[ 	]+c:[ 	]+08200420[ 	]+fmadd\.d[ 	]+\$fa0, \$fa1, \$fa1, \$fa0
[ 	]+10:[ 	]+380c16a4[ 	]+ldx\.d[ 	]+\$a0, \$r21, \$a1
[ 	]+14:[ 	]+4c000020[ 	]+jirl[ 	]+\$zero, \$ra, 0
