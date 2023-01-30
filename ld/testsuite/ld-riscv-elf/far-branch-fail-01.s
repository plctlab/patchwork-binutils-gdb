.text
.global space1
space1:
.rep 1024
	nop
.endr

.global glob
glob:
	addi x0, x0, 2

.global space2
space2:
.rep 1024
	nop
.endr
