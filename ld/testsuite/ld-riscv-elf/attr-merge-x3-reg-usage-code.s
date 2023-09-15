	.text
	.globl _start
_start:
	lla	a0, x
	lui	a1, %hi(x)
	addi	a1, a1, %lo(x)

	.data
	.word 0x0
	.globl x
x:
        .word 0x1
