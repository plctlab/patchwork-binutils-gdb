#name: MIPS PIC rejects branch absolute
#ld: -shared -T pic-reloc-absolute-lo.ld
#target: [check_shared_lib_support]
#error: \A[^\n]*: in function `foo':\n
#error:   \(\.text\+0x0\): relocation R_MIPS_PC16 against `\*ABS\*' cannot be used when making a PIC/PIE object
