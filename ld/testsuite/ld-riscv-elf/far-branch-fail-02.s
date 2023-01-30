.text
.global _start
_start:
	beq a0, a1, space1
	beq a0, a1, glob
	beq a0, a1, space2

.global glob
glob:
.global glob_orig
glob_orig:
	addi x0, x0, 1
