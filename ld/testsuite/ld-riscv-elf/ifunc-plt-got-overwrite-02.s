	.text

	.type	resolver1, @function
resolver1:
	ret
	.size	resolver1, .-resolver1

	.type	resolver2, @function
resolver2:
	ret
	.size	resolver2, .-resolver2

	.globl	ifunc1
	.type	ifunc1, %gnu_indirect_function
	.set	ifunc1, resolver1

	.globl	ifunc2
	.type	ifunc2, %gnu_indirect_function
	.set	ifunc2, resolver2


	.globl	ifunc2_ptr
	.section	.data.rel,"aw"
	.align	3
	.type	ifunc2_ptr, @object
	.size	ifunc2_ptr, 8
ifunc2_ptr:
	.dword	ifunc2
	.text
	.align	1

	.globl	main
	.type	main, @function
main:
	call ifunc1@plt
	ret
	.size main, .-main
