#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


typedef struct {
	int firstnum;
	int secondnum;
	sem_t sema;
} twoIntegers;


int main(int argc, char* argv[]){
	twoIntegers ti;
	
	if (argc != 3){
		printf("Not the right number of command line arguments\n");
		if (argc == 1){
			printf("I will make them for you, 1st number is 5, the second number is 100\n");
			ti.firstnum = 5;
			ti.secondnum = 100;
		}
		else{
			printf("exiting\n");
			return 0;
		}
	}
	else {	//argc == 3
		ti.firstnum = atoi(argv[1]);
		ti.secondnum = atoi(argv[2]);
	}
	
	
	key_t key;
	int shmid;
//	key = 12335;

	if ( (key = ftok("mykey.txt", 'Z')) == (key_t) -1){
		perror("ftok");
		return -1;
	}


	shmid = shmget(key, sizeof(twoIntegers), 0644 | IPC_CREAT);
	if(shmid < 0){
		perror("shmget");
		return -1;
	}
	
	printf("shmid: %d\n", shmid);
	char * data;
	data = shmat(shmid, (void *)0, 0);
	if(data < 0){
		perror("shmat");
		return -1;
	}	
	
	twoIntegers *aa = (twoIntegers *) data;
	sem_init(&(aa->sema), 1, 1);
	int valp;

/*
	sem_getvalue(&(aa->sema), &valp);
	printf("sema value before 1st wait: %d\n", valp);
*/
	
	pid_t pid;
	
	sem_wait(&(aa->sema));
/*
	sem_getvalue(&(aa->sema), &valp);
	printf("sema value after 1st wait: %d\n", valp);
*/
	
	pid = fork();
//fork fails
	if (pid == -1) { 
		fprintf(stderr, "fork failed\n"); 
		return -1; 
	}	
//the child	 
	if (pid == 0) { 
			
	/*
	The child reads the two integers and computes 
	the multiplication and overwrites Integer1 in 
	the share memory with the result
	*/
		sem_wait(&(aa->sema));
			printf("This is the child\n"); 
			//memcpy(&ti, data, sizeof(ti));
			int tmp1 = aa->firstnum;
			int tmp2 = aa->secondnum;
			int tmp3 = tmp1 * tmp2;
			//ti.firstnum = ti.firstnum * ti.secondnum;
		
			//memcpy(data, &ti, sizeof(ti));
			aa->firstnum = tmp3;
			aa->secondnum = tmp2;
		sem_post(&(aa->sema));
		

		int i;
		i = shmdt(data);
		if (i < 0) {
			perror("shmdt");
			exit(1);
		}
		
		exit(0); 
	}	
//the parent	
	else { 		
			printf("This is the parent\n");
			/*
			It then writes two integers to the share memory
			*/
			//memcpy(data, &ti, sizeof(ti));
			aa->firstnum = ti.firstnum;
			aa->secondnum = ti.secondnum;
		
		sem_post(&(aa->sema));
	
/*
		sem_getvalue(&(aa->sema), &valp);
		printf("sema value after 1st post: %d\n", valp);
*/
		
		
		printf("parent waits\n");
		wait(NULL);
		
		/*
		Finally the parent should read and print out the result.
		*/
		sem_wait(&(aa->sema));
			printf("This is the parent part 2\n");
//ok to use memcpy here since its copying to ti and we wont be using the sema in ti, but dont memcpy to the shared memory from ti, bad things happen, screws up the sema :<
			memcpy(&ti, data, sizeof(ti));
		sem_post(&(aa->sema));


		int d = shmctl(shmid, IPC_RMID, NULL);
		if(d<0){
			perror("shmctl");
			return -1;
		}
		
		printf("The final result: 1st int: %d, 2nd int: %d\n", ti.firstnum, ti.secondnum);
		
		
		
		return 0;
	} 
	
	

}

