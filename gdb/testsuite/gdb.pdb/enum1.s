.equ CV_SIGNATURE_C13, 4

.equ T_UQUAD, 0x0023

.equ LF_FIELDLIST, 0x1203
.equ LF_INDEX, 0x1404
.equ LF_ENUMERATE, 0x1502
.equ LF_ENUM, 0x1507

.equ LF_USHORT, 0x8002
.equ LF_LONG, 0x8003
.equ LF_UQUADWORD, 0x800a

.section ".debug$T", "rn"

.long CV_SIGNATURE_C13

# Type 1000, field list for enum enum1 (red = 0, green = 1, blue = -1, yellow = 0x8000, purple = 0x100000000)
.fieldlist1:
.short .enum1 - .fieldlist1 - 2
.short LF_FIELDLIST
.short LF_ENUMERATE
.short 3 # public
.short 0 # value
.asciz "red"
.byte 0xf2 # padding
.byte 0xf1 # padding
.short LF_ENUMERATE
.short 3 # public
.short 1 # value
.asciz "green"
.short LF_ENUMERATE
.short 3 # public
.short LF_LONG
.long 0xffffffff # value
.asciz "blue"
.byte 0xf1 # padding
.short LF_ENUMERATE
.short 3 # public
.short LF_USHORT
.short 0x8000 # value
.asciz "yellow"
.byte 0xf1 # padding
.short LF_ENUMERATE
.short 3 # public
.short LF_UQUADWORD
.quad 0x100000000 # value
.asciz "purple"
.byte 0xf3 # padding
.byte 0xf2 # padding
.byte 0xf1 # padding

# Type 1001, enum enum1
.enum1:
.short .fieldlist2 - .enum1 - 2
.short LF_ENUM
.short 3 # no. elements
.short 0 # property
.long T_UQUAD # underlying type
.long 0x1000 # field list
.asciz "enum1"
.byte 0xf2 # padding
.byte 0xf1 # padding

# Type 1002, continuation field list for enum enum2 (xyzzy = 3, plugh = 5)
.fieldlist2:
.short .fieldlist3 - .fieldlist2 - 2
.short LF_FIELDLIST
.short LF_ENUMERATE
.short 3 # public
.short 3 # value
.asciz "xyzzy"
.short LF_ENUMERATE
.short 3 # public
.short 5 # value
.asciz "plugh"

# Type 1003, field list for enum enum2 (foo = 1, bar = 1, baz = 2, ...)
.fieldlist3:
.short .enum2 - .fieldlist3 - 2
.short LF_FIELDLIST
.short LF_ENUMERATE
.short 3 # public
.short 1 # value
.asciz "foo"
.byte 0xf2 # padding
.byte 0xf1 # padding
.short LF_ENUMERATE
.short 3 # public
.short 1 # value
.asciz "bar"
.byte 0xf2 # padding
.byte 0xf1 # padding
.short LF_ENUMERATE
.short 3 # public
.short 2 # value
.asciz "baz"
.byte 0xf2 # padding
.byte 0xf1 # padding
.short LF_INDEX
.short 0 # padding
.long 0x1002

# Type 1004, enum enum2
.enum2:
.short .types_end - .enum2 - 2
.short LF_ENUM
.short 5 # no. elements
.short 0 # property
.long T_UINT4 # underlying type
.long 0x1003 # field list
.asciz "enum2"
.byte 0xf2 # padding
.byte 0xf1 # padding

.types_end:
