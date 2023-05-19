#as: -march=rv32ifv
#warning_output: vector-insns-warning.l
#objdump: -dr

.*:[ 	]+file format .*


Disassembly of section .text:

0+000 <.text>:
[ 	]+[0-9a-f]+:[ 	]+80c5f557[ 	]+vsetvl[ 	]+a0,a1,a2
[ 	]+[0-9a-f]+:[ 	]+0005f557[ 	]+vsetvli[ 	]+a0,a1,e8,m1,tu,mu
[ 	]+[0-9a-f]+:[ 	]+7ff5f557[ 	]+vsetvli[ 	]+a0,a1,2047
[ 	]+[0-9a-f]+:[ 	]+0045f557[ 	]+vsetvli[ 	]+a0,a1,4
[ 	]+[0-9a-f]+:[ 	]+0205f557[ 	]+vsetvli[ 	]+a0,a1,32
[ 	]+[0-9a-f]+:[ 	]+0015f557[ 	]+vsetvli[ 	]+a0,a1,e8,m2,tu,mu
[ 	]+[0-9a-f]+:[ 	]+04a5f557[ 	]+vsetvli[ 	]+a0,a1,e16,m4,ta,mu
[ 	]+[0-9a-f]+:[ 	]+0165f557[ 	]+vsetvli[ 	]+a0,a1,e32,mf4,tu,mu
[ 	]+[0-9a-f]+:[ 	]+09d5f557[ 	]+vsetvli[ 	]+a0,a1,e64,mf8,tu,ma
[ 	]+[0-9a-f]+:[ 	]+c005f557[ 	]+vsetivli[ 	]+a0,11,e8,m1,tu,mu
[ 	]+[0-9a-f]+:[ 	]+fff5f557[ 	]+vsetivli[ 	]+a0,11,1023
[ 	]+[0-9a-f]+:[ 	]+c045f557[ 	]+vsetivli[ 	]+a0,11,4
[ 	]+[0-9a-f]+:[ 	]+c205f557[ 	]+vsetivli[ 	]+a0,11,32
[ 	]+[0-9a-f]+:[ 	]+c015f557[ 	]+vsetivli[ 	]+a0,11,e8,m2,tu,mu
[ 	]+[0-9a-f]+:[ 	]+c4a5f557[ 	]+vsetivli[ 	]+a0,11,e16,m4,ta,mu
[ 	]+[0-9a-f]+:[ 	]+c165f557[ 	]+vsetivli[ 	]+a0,11,e32,mf4,tu,mu
[ 	]+[0-9a-f]+:[ 	]+c9d5f557[ 	]+vsetivli[ 	]+a0,11,e64,mf8,tu,ma
[ 	]+[0-9a-f]+:[ 	]+7005f557[ 	]+vsetvli[ 	]+a0,a1,1792
[ 	]+[0-9a-f]+:[ 	]+4005f557[ 	]+vsetvli[ 	]+a0,a1,1024
[ 	]+[0-9a-f]+:[ 	]+3005f557[ 	]+vsetvli[ 	]+a0,a1,768
[ 	]+[0-9a-f]+:[ 	]+1005f557[ 	]+vsetvli[ 	]+a0,a1,256
[ 	]+[0-9a-f]+:[ 	]+f005f557[ 	]+vsetivli[ 	]+a0,11,768
[ 	]+[0-9a-f]+:[ 	]+d005f557[ 	]+vsetivli[ 	]+a0,11,256
