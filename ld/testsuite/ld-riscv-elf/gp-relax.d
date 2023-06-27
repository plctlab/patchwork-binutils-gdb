#source: gp-relax.s
#ld: --relax
#objdump: -d -Mno-aliases

.*:[ 	]+file format .*


Disassembly of section \.text:

0+[0-9a-f]+ <_start>:
.*:[ 	]+[0-9a-f]+[ 	]+addi[ 	]+a5,gp,\-[0-9]+ # [0-9a-f]+ <global_array>
.*:[ 	]+[0-9a-f]+[ 	]+addi[ 	]+a4,gp,[0-9]+ # [0-9a-f]+ <person>
