	.text
Phi:
	.insn VEX.L0.f2.0f 0xae/7, 0x40(%rax)		# clevict0 0x40(%rax)
	.insn VEX.L0.f3.0f 0xae/7, 0x40(%rax)		# clevict1 0x40(%rax)
	.insn VEX.L0.f3.0f 0xae/6, %r8d			# delay %r8d
	.insn VEX.L0.f3.0f 0xae/6, %rcx			# delay %rcx
	.insn VEX.L0.W0 0x74, $Phi-1f{:s8}, %k3		# jkzd Phi, %k3
1:
	.insn VEX.L0.0f.W0 0x85, $Phi-2f{:s32}, %k4	# jknzd Phi, %k4
2:
	.insn VEX.L0.0f.W0 0x41, %k1, %k2		# kand %k1, %k2
	.insn VEX.L0.0f.W0 0x42, %k1, %k2		# kandn %k1, %k2
	.insn VEX.L0.0f.W0 0x43, %k1, %k2		# kandnr %k1, %k2
	.insn VEX.L0.0f.W0 0x95, %k1, %k2, %r8		# kconcath %k1, %k2, %r8
	.insn VEX.L0.0f.W0 0x97, %k1, %k2, %rdi		# kconcatl %k1, %k2, %rdi
	.insn VEX.L0.0f3a.W0 0x3e, $3, %r9, %k2		# kextract $3, %r9, %k2
	.insn VEX.L0.0f.W0 0x48, %k1, %k2		# kmergel1h %k1, %k2
	.insn VEX.L0.0f.W0 0x49, %k1, %k2		# kmergel1l %k1, %k2
	.insn VEX.L0.0f.W0 0x90, %k1, %k2		# kmov %k1, %k2
	.insn VEX.L0.0f.W0 0x93, %k1, %r10d		# kmov %k1, %r10d
	.insn VEX.L0.0f.W0 0x92, %r9d, %k2		# kmov %r9d, %k2
	.insn VEX.L0.0f.W0 0x44, %k1, %k2		# knot %k1, %k2
	.insn VEX.L0.0f.W0 0x45, %k1, %k2		# kor %k1, %k2
	.insn VEX.L0.0f.W0 0x98, %k1, %k2		# kortest %k1, %k2
	.insn VEX.L0.0f.W0 0x46, %k1, %k2		# kxnor %k1, %k2
	.insn VEX.L0.0f.W0 0x47, %k1, %k2		# kxor %k1, %k2
	.insn VEX.L0.f3.0f 0xbd, %r8d, %ecx		# lzcnt %r8d, %ecx
	.insn VEX.L0.f3.0f 0xbd, %rcx, %r8		# lzcnt %rcx, %r8
	.insn VEX.L0.f3.0f 0xb8, %ecx, %r8d		# popcnt %ecx, %r8d
	.insn VEX.L0.f3.0f 0xb8, %r8, %rcx		# popcnt %r8, %rcx
	.insn VEX.L0.f2.0f 0xae/6, %ecx			# spflt %ecx
	.insn VEX.L0.f2.0f 0xae/6, %r8			# spflt %r8
	.insn VEX.L0.f3.0f 0xbc, %r8d, %ecx		# tzcnt %r8d, %ecx
	.insn VEX.L0.f3.0f 0xbc, %rcx, %r8		# tzcnt %rcx, %r8
	.insn VEX.L0.f2.0f 0xbc, %ecx, %r8d		# tzcnti %ecx, %r8d
	.insn VEX.L0.f2.0f 0xbc, %r8, %rcx		# tzcnti %r8, %rcx
	.insn VEX.L0.0f 0x18/1, 0x40(%rdi)		# vprefetch0 0x40(%rdi)
	.insn VEX.L0.0f 0x18/2, 0x40(%r8)		# vprefetch1 0x40(%r8)
	.insn VEX.L0.0f 0x18/3, 0x40(%r15)		# vprefetch2 0x40(%r15)
	.insn VEX.L0.0f 0x18/5, Phi(%rip)		# vprefetche0 Phi(%rip)
	.insn VEX.L0.0f 0x18/6, (%rcx,%r8,2)		# vprefetche1 (%rcx,%r8,2)
	.insn VEX.L0.0f 0x18/7, (%r8,%rcx,4)		# vprefetche2 (%r8,%rcx,4)
	.insn VEX.L0.0f 0x18/4, (,%rax,8)		# vprefetchenta (,%rax,8)
	.insn VEX.L0.0f 0x18/0, 0x40(%rax)		# vprefetchnta 0x40(%rax)
