MEMORY {
  rom : ORIGIN = 0x0000, LENGTH = 0x4000
  ram : ORIGIN = 0x4000, LENGTH = 0x1000
}

SECTIONS
{
  .text : {
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
  .data : AT (0x4000) { *(.data) } >ram /* NO default AT>rom */
  . = ALIGN(0x20);
  .bss : { *(.bss) } >ram /* NO default AT>rom */

  /DISCARD/ : { *(*) }
}
