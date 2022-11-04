.attribute arch, "rv64ic"
nop		# $xrv64i2p0_c2p0
.option push
.option arch, +d2p0, -c, +xvendor1p0
nop		# $xrv64i2p0_f2p0_d2p0_xvendor1p0
frcsr	a0
.option push
.option arch, +m3p0, +d3p0, +xvendor32x3p0
nop		# $xrv64i2p0_m3p0_f2p0_d2p0_zmmul1p0_xvendor1p0_xvendor32x3p0
.option pop
.option pop
.option arch, rv32i2p1c2p0
nop		# $xrv32i2p1_c2p0
