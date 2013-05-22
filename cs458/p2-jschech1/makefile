all: des

des: des.c
	gcc -g des.c -o des -lcrypto -I/usr/local/ssl/include
#	gcc -g des.c -o des -lcrypto -I/usr/local/ssl/include -L/usr/local/ssl/lib

clean: 
	rm -f des