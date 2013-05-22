#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#include <sys/time.h>


//       ./partA numchildren MaxVal

typedef struct {
	long long firstnum;
	long long secondnum;
	int winnerpid;
	
	int childcounter;
	int AllKidsReady;
	
	unsigned int totalwaitingtime;
	
	
	sem_t childlock;
	sem_t sema;
} threeIntegers;


int main(int argc, char* argv[]){

	struct timeval start;
	if(gettimeofday(&start, 0) != 0){
		printf("getting time 1 failed, exiting\n");
		return 0;
	}
//	double dstart = start.tv_sec + (start.tv_usec/1000000.0);
	printf("Time Start:\t sec = %ld\t microsec = %ld\n", start.tv_sec, start.tv_usec);
	double dmath;
	
	struct timeval childgetslock;
	double dch = 0;
	int childgetslockint = 0;
	struct timeval end;
	double dend = 0;
//	struct timeval math;


	int numchildren;
	long long MaxVal;
	
	
	if (argc != 3){
		printf("Not the right number of command line arguments\n");
		printf("exiting\n");
		return 0;
	}
	else {	//argc == 3
		numchildren = atoi(argv[1]);
		MaxVal = atoll(argv[2]);
	}
	
	printf("\nMAXVAL == %lld\n", MaxVal);
	
	

	key_t key;
	int shmid;
	if ( (key = ftok("mykey.txt", 'p')) == (key_t) -1){
		perror("ftok");
		return -1;
	}

	shmid = shmget(key, sizeof(threeIntegers), 0644 | IPC_CREAT);
	if(shmid < 0){
		perror("shmget");
		return -1;
	}
	
//	printf("shmid: %d\n", shmid);
	char * data;
	data = shmat(shmid, (void *)0, 0);
	if(data < 0){
		perror("shmat");
		return -1;
	}

	threeIntegers *aa = (threeIntegers *) data;
	
	aa->firstnum = 1;
	aa->secondnum = 2;
	aa->winnerpid = 0;
	sem_init(&(aa->sema), 1, 1);
	sem_init(&(aa->childlock), 1, 1);
	aa->childcounter = 0;
	
	aa->AllKidsReady = 0;

	aa->totalwaitingtime = 0;

	int pid = 1;//parent pid >0
	int i;
	for(i=0; i<numchildren; i++){ //makes cval # of kids, only the parent will do it, it checks pid, kids =0
		if(pid>0){
			if ((pid = fork()) < 0) { 
				fprintf(stderr, "fork failed\n"); 
				exit(1); 
			}
			
			if(pid > 0){
//				printf("\nParent created %d\n", pid);
			}
			
		}
	}

	//the child	 
	if (pid == 0)
	{
//		printf("\t\t\tchildpid = %d\n", getpid());
		long long tmp1 = 0;
		long long tmp2 = 0;
		long long tmp3 = 0;
		struct timeval childmath;
		
		sem_wait(&(aa->childlock));
			aa->childcounter = aa->childcounter + 1;
		sem_post(&(aa->childlock));
		
		int akir = aa->AllKidsReady;
		while(akir == 0){
			//printf("%d: kids not all ready\n", getpid());
			sched_yield();
			akir = aa->AllKidsReady;
		}
		
		if(gettimeofday(&childmath, 0) != 0){
			printf("getting time 2 failed, exiting\n");
			exit(0);
		}
		printf("%d wants lock:\t sec = %ld\t microsec = %ld\n", getpid(), childmath.tv_sec, childmath.tv_usec);
		
		
		//bool bl = true;
		while(1)
		{
			while ( sem_trywait(&(aa->sema)) < 0 ) {
				if( errno == EAGAIN)
					sched_yield();
				else perror("trywait error");
			}

				if(childgetslockint == 0){
					childgetslockint++;
					if(gettimeofday(&childgetslock, 0) != 0){
						printf("getting time 3 failed, exiting\n");
						exit(0);
					}
					/*
					printf("%d:\t%ld\t%ld\n", getpid(), childgetslock.tv_usec, start.tv_usec);
					childmath.tv_usec = childgetslock.tv_usec - start.tv_usec;
					printf("%d : Time to get lock = %ld microseconds\n", getpid(), childmath.tv_usec);
					*/
					printf("%d gets lock:\t sec = %ld\t microsec = %ld\n", getpid(), childgetslock.tv_sec, childgetslock.tv_usec);
					dmath = ( (childgetslock.tv_sec * 1000000.0) + childgetslock.tv_usec) - ((childmath.tv_sec * 1000000.0) + childmath.tv_usec);
					aa->totalwaitingtime = aa->totalwaitingtime + dmath;
					printf("%d TIME TO GET THE LOCK: \t%f microseconds\n", getpid(), dmath);
//					dch = childgetslock.tv_sec + (childgetslock.tv_usec/1000000.0);
//					printf("%d:\tTIME TO GET LOCK: %f seconds\n", getpid(), dch - dstart);
				}
				
//				printf("pid = %d: ENGAGED\n", getpid());
			
				tmp1 = aa->firstnum;
				tmp2 = aa->secondnum;
				if( (tmp1 > MaxVal) || (tmp2 > MaxVal) )
				{
//					printf("first if, tmp1 = %lld, tmp2 = %lld\n", tmp1, tmp2);
					sem_post(&(aa->sema));
					exit(0);
				}

				tmp3 = tmp1 + tmp2;

				if(tmp1 <= tmp2)
				{
//					printf("second if, tmp1 = %lld, tmp2 = %lld\n", tmp1, tmp2);
					aa->firstnum = tmp3;
				}
				else //tmp1 > tmp2
				{
//					printf("third if, tmp1 = %lld, tmp2 = %lld\n", tmp1, tmp2);
					aa->secondnum = tmp3;
				}


				if(tmp3 > MaxVal)
				{
//					printf("fourth if, tmp1 = %lld, tmp2 = %lld\n", tmp1, tmp2);
					aa->winnerpid = getpid();
				}
			
			sem_post(&(aa->sema));
			//printf("\n");
			sched_yield();
			
			
			
		}
	}

	//the Parent
	else {
		while(numchildren != aa->childcounter){
			continue;
		}
	
		printf("\n\nPARENT UNLOCKS THE WORLD\n\n");
		aa->AllKidsReady = 1;
		
		for(i=0; i<numchildren; i++){
			wait(NULL);
		}
		
		sem_wait(&(aa->sema));
			printf("\n\nThe winner has pid: %d\n", aa->winnerpid);
		sem_post(&(aa->sema));
		sem_destroy(&(aa->sema));
		
		int d = shmctl(shmid, IPC_RMID, NULL);
		if(d<0){
			perror("shmctl");
			return -1;
		}
		
		if(gettimeofday(&end, 0) != 0){
			printf("getting time 4 failed, exiting\n");
			return 0;
		}
		/*
		math.tv_usec = end.tv_usec - start.tv_usec;
		printf("Time to end: %ld microseconds\n", math.tv_usec);
		*/
		printf("Time End: \t sec = %ld\t microsec = %ld\n", end.tv_sec, end.tv_usec);
		dend = end.tv_sec + (end.tv_usec/1000000.0);
		
		dmath = ( (end.tv_sec * 1000000.0) + end.tv_usec) - ((start.tv_sec * 1000000.0) + start.tv_usec);
		printf("TIME IT TAKES TO END: \t%f microseconds\n", dmath);
		printf("Average time for the lock: %d\n",  (aa->totalwaitingtime)/numchildren);
//		printf("Time to end:\t%f seconds\n", dend - dstart);

		
		
		return 0;
	}

	return 0;
}








