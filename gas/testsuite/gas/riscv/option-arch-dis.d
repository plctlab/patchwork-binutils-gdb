#as: -misa-spec=2.2
#source: option-arch.s
#objdump: -d

.*:[   ]+file format .*


Disassembly of section .text:

0+000 <.text>:
[ 	]+[0-9a-f]+:[  	]+0001[    	]+nop
[ 	]+[0-9a-f]+:[  	]+00000013[    	]+nop
[ 	]+[0-9a-f]+:[  	]+00302573[    	]+frcsr[        	]+a0
[ 	]+[0-9a-f]+:[  	]+00000013[    	]+nop
[ 	]+[0-9a-f]+:[  	]+0001[    	]+nop
