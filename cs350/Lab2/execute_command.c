#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>


int main(int argc, char* argv[]){
	if(argc == 1){
		printf("\nYou didn't say what to do\nEXITING\n");
		return 0;
	}

	pid_t pid;
	
	if ((pid = fork()) < 0) { 
		fprintf(stderr, "fork failed\n"); 
		exit(1); 
	}
		
	if (pid == 0) { 
		if(execvp(argv[1], &argv[1]) == -1)	
			fprintf(stderr, "execvp failed\n"); 
		exit(2); 
	}
	
	
	wait();
	return 0;
}
