	.text
	.globl	global_var
	.section	.sbss,"aw",@nobits
	.align	2
	.type	global_var, @object
	.size	global_var, 4
global_var:
	.zero	4
	.globl	global_array
	.bss
	.align	3
	.type	global_array, @object
	.size	global_array, 3680
global_array:
	.zero	3680
	.globl	person
	.align	3
	.type	person, @object
	.size	person, 428
person:
	.zero	428
	.text
	.align	1
	.globl	_start
	.type	_start, @function
_start:
	lui	a5,%hi(global_array)
	addi	a5,a5,%lo(global_array)

	lui	a4,%hi(person)
	addi	a4,a4,%lo(person)
