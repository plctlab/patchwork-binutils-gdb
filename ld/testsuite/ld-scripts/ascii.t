MEMORY {
  rom : ORIGIN = 0x000000, LENGTH = 0x400000
  ram : ORIGIN = 0x400000, LENGTH = 0x10000
}

_start = 0x000000;
SECTIONS
{
  . = 0x1000 + SIZEOF_HEADERS;
  .text ALIGN (0x100) :

    {
      INCLUDE "header.inc"

      FILL(0xFF)
      entry = .;
      *(.text)
      . = ALIGN(0x100);
      ASCII (128) "This is a string, 128 byte long"
/*      ASCII 32,"This is a string" */
      LONG(ecc_start)
      . = ALIGN(16);
      align_label = .;
      ASCIZ "This is an unaligned string"
      unalign_label = .;
      BYTE(1)
      BYTE(2)
      BYTE(3)
      BYTE(4)
      BYTE(4)
      BYTE(7)
      BYTE(1)
      BYTE(1)
      . = ALIGN(16);
      BYTE(1)
      . = ALIGN(16);
      ASCII (8) "This is way too long"
      . = ALIGN(16);
      ASCII (64) "I meant to say: This is way too long"
      . = ALIGN(1024);
      ASCII (512) "A very long string followed by a '01'"
      BYTE(1)
      ecc_end = .;
    } > rom

  .data : AT (0x400000) { *(.data) } >ram /* NO default AT>rom */
  . = ALIGN(0x20);
  .bss : { *(.bss) } >ram /* NO default AT>rom */
  /DISCARD/ : { *(*) }
}

