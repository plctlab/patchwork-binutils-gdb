#source: tp_as_gp.s
#as:
#ld: --relax --tp-as-gp
#objdump: -d


.*:[ 	]+file format .*

Disassembly of section \.text:

0+[0-9a-f]+ <_start>:
.*:[ 	]+[0-9a-f]+[ 	]+lui[ 	]+a5,.*
.*:[ 	]+[0-9a-f]+[ 	]+add[ 	]+a5,a5,[0-9]+ # [0-9a-f]+ <global_array>
.*:[ 	]+[0-9a-f]+[ 	]+add[ 	]+a5,tp,\-[0-9]+ # [0-9a-f]+ .*