#PROG: objcopy
#name: objcopy rename-section with flags - keep relocation
#source: needed-by-reloc.s
#objcopy: --rename-section .data=rodata,contents,alloc,load,readonly
#objdump: -r

.*: +file format .*

RELOCATION RECORDS FOR \[rodata\]:
OFFSET +TYPE +VALUE
0+ +[^ ]+ +foo

