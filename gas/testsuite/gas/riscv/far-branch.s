target:
	bne a0, a1, target
.rep 1024
	nop
.endr
	bne a0, a1, target
