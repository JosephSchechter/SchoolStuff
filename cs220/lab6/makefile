# Joseph Schechter lab6 makefile
all: repeat repeat2 repeat3 repeat4 repeat5 test test2 test3 test4 test5
#####################################
repeat.o: repeat.s
	gcc -Wall -c repeat.s -o repeat.o
repeat.s: repeat.c
	gcc -Wall -S repeat.c -o repeat.s
#####################################	
repeat: repeat.o show.o
	gcc -Wall repeat.o show.o -o repeat
show.o: show.s
	gcc -Wall -c show.s -o show.o
show.s: show.c
	gcc -Wall -S show.c -o show.s
######################################
repeat2: repeat.o show2.o
	gcc -Wall repeat.o show2.o -o repeat2
show2.o: show2.s
	gcc -Wall -c show2.s -o show2.o
######################################
repeat3: repeat.o show3.o
	gcc -Wall repeat.o show3.o -o repeat3
show3.o: show3.s
	gcc -Wall -c show3.s -o show3.o
######################################
repeat4: repeat.o show4.o
	gcc -Wall repeat.o show4.o -o repeat4
show4.o: show4.s
	gcc -Wall -c show4.s -o show4.o
######################################
repeat5: repeat.o show5.o
	gcc -g -Wall repeat.o show5.o -o repeat5
show5.o: show5.s
	gcc -g -Wall -c show5.s -o show5.o
#####################################	
test.o: test.s
	gcc -Wall -c test.s -o test.o
test.s: test.c
	gcc -Wall -S test.c -o test.s
###################################
test: test.o show.o
	gcc -Wall test.o show.o -o test
######################################	
test2: test.o show2.o
	gcc -Wall test.o show2.o -o test2
####################################
test3: test.o show3.o
	gcc -Wall test.o show3.o -o test3
####################################
test4: test.o show4.o
	gcc -Wall test.o show4.o -o test4
####################################
test5: test.o show5.o
	gcc -Wall test.o show5.o -o test5
####################################