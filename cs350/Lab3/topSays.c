// Joseph Schechter
//   ./topSays 5
//will create a parent, forks a child, and that child will fork another until there are 5 children
//the parent pipes a message to the lowest child
//lowest child prints the message

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	pid_t pid;
	int totalChildren = atoi(argv[1]);
	if(totalChildren <= 0){
		printf("\nN <= 0, exiting\n");
		return(0);
	}
	int children = totalChildren;
	int pfds[2];
	char buf[30];
	
	
	//create pipe
	if(pipe(pfds) == -1){
		perror("PIPE");
		exit(1);
	}

	//fork 1st time,
	if ( (pid = fork()) < 0) {
		perror("fork");
		exit(1);
   	}
	
	//if(pid == 0) printf("fork\n");
	children--;
	
	if(pid==0){ //is any child
	
		while(children>0 && pid==0){
			if ( (pid = fork()) < 0) {  //fork a 2nd time, 3rd 4th...., 
			// ^ ^ will change all but baby child into a parent pid
				perror("fork");
				exit(1);
			}
			//if(pid == 0) printf("fork\n");
			children--;		
		}
		
		if(pid==0){ //only the baby child will do this, since it exits the while with pid==0 since children=0
			close(pfds[1]); //close writing
			if( read(pfds[0], buf, 30) <= 0 ) { //reads into buffer
				perror("child");
				exit(1);
			}
			printf("READING: \"%s\"\n" , buf); //prints buffer
			exit(2);			
		}
		else{//is a middle child
			close(pfds[1]);
			wait(NULL); //waits for the lower child
			exit(2); 
		}
	}
	
	
	else{ //is the original parent
	close(pfds[0]); //close reading end;
	
	//parent writes to pipe
		if(write(pfds[1], "HOLA!", 10) <= 0) {
			perror("PARENT ERROR WRITING");
			exit(1);
		}
	}
	
	wait(NULL); //waits for eldest to end
	
	printf("\n\n");

	return(0);
}