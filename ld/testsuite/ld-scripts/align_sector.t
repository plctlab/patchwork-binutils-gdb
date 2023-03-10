MEMORY {
  rom : ORIGIN = 0x0000, LENGTH = 0x4000
  ram : ORIGIN = 0x4000, LENGTH = 0x1000
}

BANK ( dummy0 ) {
  SECTOR ("32kB");
}

BANK ( bank0 ) {
  SECTOR ("1 KB");
  SECTOR ("1 KB");
  SECTOR ("1 KB");
  SECTOR ("1 KB");
  SECTOR ("2 KB");
  SECTOR ("2 KB");
}

SECTIONS
{
  .text : {
	. = ALIGN(0x8000);
	FILL(0xFF)
	sector0 = .;
	ASCIZ "sector0"
	*(.text .pr)
	ALIGN_SECTOR
	sector1 = .;
	ASCIZ "sector1"
	ALIGN_SECTOR
	sector2 = .;
	ASCIZ "sector2"
	ALIGN_SECTOR
	sector3 = .;
	ASCIZ "sector3"
	ALIGN_SECTOR
	sector4 = .;
	ASCIZ "sector4"
	ALIGN_SECTOR
	sector5 = .;
	ASCIZ "sector5"
	ALIGN_SECTOR
	sector6 = .;
	ASCIZ "sector6"
	. = ALIGN(0x10);
  } >  rom
  .data : AT (0x400000) { *(.data) } >ram /* NO default AT>rom */
  . = ALIGN(0x20);
  .bss : { *(.bss) } >ram /* NO default AT>rom */

  /*
  ASSERT (sector0 == 0x0000, "Bad Address: sector0")
  ASSERT (sector1 == 0x0400, "Bad Address: sector1")
  ASSERT (sector2 == 0x0800, "Bad Address: sector2")
  ASSERT (sector3 == 0x0C00, "Bad Address: sector3")
  ASSERT (sector4 == 0x1000, "Bad Address: sector4")
  ASSERT (sector5 == 0x1800, "Bad Address: sector5")
  ASSERT (sector6 == 0x2000, "Bad Address: sector6")
  */
  /DISCARD/ : { *(*) }
}
