#source: attr-merge-x3-reg-usage-code.s
#source: attr-merge-x3-reg-usage-attrs.s
#as: --defsym __relax__=1
#ld:
#objdump: -d -Mno-aliases

.*:[ 	]+file format .*


Disassembly of section \.text:

0+[0-9a-f]+ <_start>:
.*:[ 	]+[0-9a-f]+[ 	]+addi[ 	]+a0,gp,\-[0-9]+ # [0-9a-f]+ <x>
.*:[ 	]+[0-9a-f]+[ 	]+addi[ 	]+a1,gp,\-[0-9]+ # [0-9a-f]+ <x>
