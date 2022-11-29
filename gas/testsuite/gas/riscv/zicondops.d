#as: -march=rv32i_zicondops
#source: zicondops.s
#objdump: -d

.*:[ 	]+file format .*

Disassembly of section .text:

0+000 <target>:
[ 	]+[0-9a-f]+:[ 	]+06c5d533[ 	]+czero\.eqz[ 	]+a0,a1,a2
[ 	]+[0-9a-f]+:[ 	]+06f776b3[ 	]+czero\.nez[ 	]+a3,a4,a5
