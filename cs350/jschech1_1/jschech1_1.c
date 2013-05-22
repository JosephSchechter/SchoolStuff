#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc == 3 || argc == 4){	

		int hval = atoi(argv[1]);
		int cval = atoi(argv[2]);
		int numTabs;
		
		if(argc == 3){
			numTabs = 0;
		}
		else{
			numTabs = atoi(argv[3]);
		}
		
//		printf("%d %d %d\n", hval, cval, numTabs);
		
		if(cval == 0){
			printf("\nZERO CHILDREN, exiting\n");
			return 0;
		}
		
		int j = 0;
		for (j=0; j<numTabs; j++)
			printf("\t");
		printf("(%d): Process starting\n", getpid());
		
		for (j=0; j<numTabs; j++)
			printf("\t");
		printf("(%d): Parent's ID: %d\n", getpid(), getppid());
		
		for (j=0; j<numTabs; j++)
			printf("\t");
		printf("(%d): Height in tree = %d \n", getpid(), hval);
		
		if(hval>1){
			for (j=0; j<numTabs; j++)
				printf("\t");
			printf("(%d): Creating %d Children at height %d \n", getpid(), cval, hval-1);
		}
		else{
	//		printf("hval bad, quitting\n");
			for (j=0; j<numTabs; j++)
				printf("\t");
			printf("(%d): Terminating at height (%d)\n", getpid(), hval);
			exit(4);
		}
		
		
		int pid = 1;//parent pid >0
		
		int i=0;
		for(i=0; i<cval; i++){ //makes cval # of kids, only the parent will do it, it checks pid, kids =0
			if(pid>0){
				if ((pid = fork()) < 0) { 
					fprintf(stderr, "fork failed\n"); 
					exit(1); 
				}
			}
		}
		
		
		if(pid > 0){	//is a parent, just waits for all children to end
			int z;
			for(z=0; z<cval; z++){
				wait(NULL);
			}
			for (j=0; j<numTabs; j++)
				printf("\t");
			//printf("(%d): Process Ending\n", getpid());
			printf("(%d): Terminating at height (%d)\n", getpid(), hval);
			
		}
		else{	//is a child
			char heightString[100];
			char childString[100];
			
			int newH = hval-1;
			
			char charTabs[100];
			sprintf(charTabs, "%d", numTabs+1);
			
			sprintf(heightString, "%d", newH);
			sprintf(childString, "%d", cval);
	//		printf("(%d): HI FROM CHILD\n", getpid());
	//		printf("(%d): Process Ending\n", getpid());
			
			if( execlp("./jschech1_1", 
							"jschech1_1", 
							heightString,
							childString,
							charTabs,
							(char *) NULL) == -1)
			{
				fprintf(stderr, "execlfailed\n"); 
			}
			
			exit(3);
		}

		
		return 0;
	}
	
	else{
		printf("\nweird input numbers\n");
		return 0;
	}
}


//	int peppid = getppid();
//	printf("%d\n", peppid);

/*
   1.   Your program should accept two command-line arguments H and C that describe the structure of the process tree. The argument H is the height of the tree and C is the number of child processes belonging to each internal node of the process tree.
   2. Upon starting up, your program should first print the following information:

      		(pid): Process starting
      		(pid): Parent's id = (ppid)
      		(pid): Height in the tree = (value_of_H_from_command_line_argument)
      		(pid): Creating (value_of_C_from_command_line) children at height (H-1)

      In the above output, you should replace pid by the process id of the current process and ppid by the process id of the parent process.
   3. Next, if the height H is greater than 1, your program should create C child processes using fork(), and wait for all of the children to complete using the wait() system call.
   4. Once all the child processes (if any) have terminated, your program should quit by printing.

      		(pid): Terminating at height (H).

      Parent must not quit before ALL child processes terminate.
      Also, parent must call wait() ONLY AFTER CREATING ALL CHILDREN. (Think why?)
   5. What should each child process do while the parent waits? Recursion! Each of the child processes should use the exec() system call to run exactly the same program image as the parent. The only difference should be that the command-line argument received by the child proceses from the parent (via the exec() system call) should be H-1 for height and C for number of children.
      (NOTE: Recursion in this step can also be done without using exec(), via straightforward function calls. But you are REQUIRED to use exec() to start the child program image and pass arguments to it. Learning about exec() is one of the goals of this assignment.)
   6. Make the output more readable by neatly indenting the print statements above to match height of each process in the process heirarchy. (Do this at the end. Its worth only 5 points, but makes the TA's life easier while grading).

   */