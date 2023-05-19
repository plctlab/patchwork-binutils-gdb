	vsetvl   a0, a1,  a2
	vsetvli  a0, a1,  0
	vsetvli  a0, a1,  0x7ff
	vsetvli  a0, a1,  0x4		# unrecognized vlmul
	vsetvli  a0, a1,  0x20		# unrecognized vsew
	vsetvli  a0, a1,  e8,  m2
	vsetvli  a0, a1,  e16, m4, ta
	vsetvli  a0, a1,  e32, mf4, mu
	vsetvli  a0, a1,  e64, mf8, tu, ma
	vsetivli a0, 0xb, 0
	vsetivli a0, 0xb, 0x3ff
	vsetivli a0, 0xb, 0x4		# unrecognized vlmul
	vsetivli a0, 0xb, 0x20		# unrecognized vsew
	vsetivli a0, 0xb, e8,  m2
	vsetivli a0, 0xb, e16, m4, ta
	vsetivli a0, 0xb, e32, mf4, mu
	vsetivli a0, 0xb, e64, mf8, tu, ma

	vsetvli  a0, a1,  0x700
	vsetvli  a0, a1,  0x400
	vsetvli  a0, a1,  0x300
	vsetvli  a0, a1,  0x100
	vsetivli a0, 0xb, 0x300
	vsetivli a0, 0xb, 0x100
