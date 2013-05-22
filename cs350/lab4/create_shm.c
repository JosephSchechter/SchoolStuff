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
	char array[512];
} solution;

int main(int argc, char* argv[])
{
	if (argc != 4){
		printf("Not the right number of arguments, exiting\n");
		return 0;
	}
	

	solution slt;
	
	sprintf(slt.array, "%s", argv[1]);
	slt.firstnum = atoi(argv[2]);
	slt.secondnum = atoi(argv[3]);
	
	
	key_t key;
	int shmid;
	if ( (key = ftok("mykey.txt", 'A')) == (key_t) -1){
		perror("ftok");
		return -1;
	}
	
	shmid = shmget(key, sizeof(slt), 0644 | IPC_CREAT);
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
	
	memcpy(data, &slt, sizeof(slt));

/*	if (i < 0) {
		perror("memcpy");
		return -1;
	}
*/
	int i;
	i = shmdt(data);
	if (i < 0) {
		perror("shmdt");
		return -1;
	}


	return 0;
}
