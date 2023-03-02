#PROG: elfedit
#elfedit: --output-flags 12345678
#source: empty.s
#readelf: -h
#name: Update ELF header 8 (decimal e_flags value)
#target: *-*-linux* *-*-gnu*

#...
  Flags:[ \t]+0xbc614e.*
#...
