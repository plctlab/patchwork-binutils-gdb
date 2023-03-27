target:
	# fli.[sdqh]: Invalid value field
	fli.s	ft1, 1
	fli.d	ft1, -1
	fli.q	ft1, 1.250
	fli.h	ft1, 8
	fli.s	ft1, infinity
	fli.d	ft1, invalid
	fli.q	ft1, 30
	fli.h	ft1, 31
	fli.s	ft1, 32
	fli.d	ft1, 0
	fli.q	ft1, 0.0
	fli.h	ft1, -0.0

	# fcvtmod.w.d: Requires explicit rounding mode.
	fcvtmod.w.d	a0, ft1

	# fcvtmod.w.d: Rounding mode other than rtz are reserved.
	fcvtmod.w.d	a0, ft1, rne
	fcvtmod.w.d	a0, ft1, rdn
	fcvtmod.w.d	a0, ft1, rup
	fcvtmod.w.d	a0, ft1, rmm
	fcvtmod.w.d	a0, ft1, dyn
	# fcvtmod.w.d: Invalid rounding mode is invalid.
	fcvtmod.w.d	a0, ft1, invalid
