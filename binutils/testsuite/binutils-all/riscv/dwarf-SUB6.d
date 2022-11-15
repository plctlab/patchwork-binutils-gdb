#PROG: objcopy
#objdump: --dwarf=frames

tmpdir/riscvcopy.o:     file format elf32-littleriscv

Contents of the .eh_frame section:


00000000 00000020 00000000 CIE
  Version:               3
  Augmentation:          "zR"
  Code alignment factor: 1
  Data alignment factor: -4
  Return address column: 1
  Augmentation data:     1b
  DW_CFA_def_cfa_register: r2 \(sp\)
  DW_CFA_def_cfa_offset: 48
  DW_CFA_offset: r1 \(ra\) at cfa-4
  DW_CFA_offset: r8 \(s0\) at cfa-8
  DW_CFA_def_cfa: r8 \(s0\) ofs 0
  DW_CFA_restore: r1 \(ra\)
  DW_CFA_restore: r8 \(s0\)
  DW_CFA_def_cfa: r2 \(sp\) ofs 48
  DW_CFA_def_cfa_offset: 0
  DW_CFA_nop

00000024 00000010 00000028 FDE cie=00000000 pc=0000002c..0000002c
  DW_CFA_nop
  DW_CFA_nop
  DW_CFA_nop

