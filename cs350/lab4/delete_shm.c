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

	key_t key;
	int shmid;

	if ( (key = ftok("mykey.txt", 'A')) == (key_t) -1){
		perror("ftok");
		return -1;
	}
	shmid = shmget(key, sizeof(solution), 0644 | IPC_CREAT);
	if(shmid < 0){
		perror("shmget");
		return -1;
	}

	int i = shmctl(shmid, IPC_RMID, NULL);
	if(i<0){
		perror("shmctl");
		return -1;
	}

	return 0;
}
