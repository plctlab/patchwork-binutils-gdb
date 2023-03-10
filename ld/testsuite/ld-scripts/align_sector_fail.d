# source: align_sector_fail.s
# ld: -T align_sector_fail.t
# error: .*: 'ALIGN_SECTOR' needs to be preceeded by a 'BANK' command.*
# target: [is_elf_format] [is_coff_format]
# notarget: [is_aout_format]
# skip: tic4x-*-* tic54x-*-*
# skip: ns32k-pc532-macho, pdp11-dec-aout, powerpc-ibm-aix5.2.0
# skip: rs6000-aix4.3.3, alpha-linuxecoff
