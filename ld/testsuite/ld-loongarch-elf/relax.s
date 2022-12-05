# m.c: printf global int a, compile with gcc -fpic.
# la.local and la.global would be relaxed to pcaddi.

	.file	"m.c"
	.text
	.globl	a
	.data
	.align	2
	.type	a, @object
	.size	a, 4
a:
	.word	123
	.section	.rodata
	.align	3
.LC0:
	.ascii	"%d\012\000"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
.LFB0 = .
	.cfi_startproc
	addi.d	$r3,$r3,-16
	.cfi_def_cfa_offset 16
	st.d	$r1,$r3,8
	stptr.d	$r22,$r3,0
	.cfi_offset 1, -8
	.cfi_offset 22, -16
	addi.d	$r22,$r3,16
	.cfi_def_cfa 22, 0
	la.global	$r12,a
	ldptr.w	$r12,$r12,0
	or	$r5,$r12,$r0
	la.local	$r4,.LC0
	#bl	%plt(printf)
	or	$r12,$r0,$r0
	or	$r4,$r12,$r0
	ld.d	$r1,$r3,8
	.cfi_restore 1
	ldptr.d	$r22,$r3,0
	.cfi_restore 22
	addi.d	$r3,$r3,16
	.cfi_def_cfa_register 3
	jr	$r1
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.0.0 20221023 (experimental)"
	.section	.note.GNU-stack,"",@progbits
