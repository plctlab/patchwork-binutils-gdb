#as: -march=rv32i
#objdump: -d

.*:[ 	]+file format .*


Disassembly of section .text:

0+000 <target>:
[^:]+:[ 	]+00b51063[ 	]+bne[ 	]+a0,a1,0 <target>
#...
[^:]+:[ 	]+00b50463[ 	]+beq[ 	]+a0,a1,.*
[^:]+:[ 	]+ff9fe06f[ 	]+j[ 	]+0 <target>
