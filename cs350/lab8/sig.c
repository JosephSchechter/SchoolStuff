#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>
#include <signal.h>

void print1(void){
	printf("OH NO!!!\n");
}


int main(int argc, char* argv[]){
	while(1){
		signal(SIGINT, print1);
		signal(SIGTSTP, print1);
	}
	
	
	return 0;
}
