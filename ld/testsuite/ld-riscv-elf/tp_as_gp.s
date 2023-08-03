	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text

	.globl	global_array
	.bss
	.align	3
	.type	global_array, @object
	.size	global_array, 5600
global_array:
	.zero	5600
        
	.globl	global_array2
	.bss
	.align	3
	.type	global_array3, @object
	.size	global_array3, 200
global_array2:
	.zero	200

	.text
	.align	1
	.globl	_start
	.type	_start, @function
_start:
	lui	a5,%hi(global_array)
	addi	a5,a5,%lo(global_array)

	lui	a5,%hi(global_array2)
	addi	a5,a5,%lo(global_array2)

