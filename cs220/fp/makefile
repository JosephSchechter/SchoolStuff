# Joseph Schechter Final Project makefile

all: final fpO1.s fpO2.s fpO3.s 
final: finalmain.o fp.o
	gcc -Wall finalmain.o fp.o -o final
######################################
finalmain.o: finalmain.s
	gcc -Wall -c finalmain.s -o finalmain.o
finalmain.s: finalmain.c
	gcc -Wall -S finalmain.c -o finalmain.s
#####################################	
fp.o: fp.s
	gcc -Wall -c fp.s -o fp.o
fp.s: fp.c
	gcc -Wall -S fp.c -o fp.s
###################Optimizations#######
fpO1.s: fp.c
	gcc -Wall -S fp.c -O -o fpO1.s
fpO2.s: fp.c
	gcc -Wall -S fp.c -O2 -o fpO2.s
fpO3.s: fp.c
	gcc -Wall -S fp.c -O3 -o fpO3.s