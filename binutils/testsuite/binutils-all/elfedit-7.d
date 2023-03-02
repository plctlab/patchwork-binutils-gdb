#PROG: elfedit
#elfedit: --output-flags 0xfedcba98
#source: empty.s
#readelf: -h
#name: Update ELF header 7 (hexadecimal e_flags value)
#target: *-*-linux* *-*-gnu*

#...
  Flags:[ \t]+0xfedcba98.*
#...
