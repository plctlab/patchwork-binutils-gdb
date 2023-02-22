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
      FILL(0xFF)
      QUAD(0xEFBEADDE45444F43);
      crc64 = .;
      DEBUG OFF
      DIGEST POLYI(64, 0xDEADBEEFDEADBEEF)(ecc_start , ecc_end)
      DEBUG OFF
      ecc_start = .;
      QUAD(ecc_start)
      QUAD(ecc_end);
      QUAD(ecc_end - ecc_start);
      QUAD(0x45444F43EFBEADDE);
      entry = .;
      *(.text)
      . = ALIGN(0x100);
      BYTE(1)
      . = ALIGN(4096) - 8;
      QUAD(0xEFBEADDE45444F43);
      DIGEST TABLE
      QUAD(0xEFBEADDE45444F43);
      QUAD(0);
      ecc_end = .;
    } > rom

  .data : AT (0x400000) { *(.data) } >ram /* NO default AT>rom */
  . = ALIGN(0x20);
  .bss : { *(.bss) } >ram /* NO default AT>rom */
  /DISCARD/ : { *(*) }
}
