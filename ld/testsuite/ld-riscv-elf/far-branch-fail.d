#name: fail on branch overflows
#source: far-branch-fail-01.s
#source: far-branch-fail-02.s RUN_OBJCOPY
#objcopy_objects: -W glob
#objdump: -d
#ld:
#error: .*relocation truncated to fit: R_RISCV_BRANCH against symbol.*glob.*
