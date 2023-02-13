#source: asciz.s
#ld: -T asciz.t
#objdump: -s -j .text
#notarget: [is_aout_format]
#xfail: tic4x-*-* tic54x-*-*

.*:     file format .*

Contents of section .text:
 10c0 434f4445 54686973 20697320 61207374  CODEThis is a st
 10d0 72696e67 00000000 00000000 00000000  ring............
 10e0 54686973 20697320 616e6f74 68657220  This is another 
 10f0 73747269 6e6700                      string.
#pass
