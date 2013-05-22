#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <pthread.h>

int A_Lock = 0;
int BNum1 = 0;

int AFac = 0;
char str[64];

pthread_mutex_t mut;


void *thread_A_func(){
	printf("THREAD A\n");
	pthread_mutex_lock(&mut);
	//A wakes up
	printf("A WAKES UP\n");
	int counter = BNum1;
	AFac = BNum1;

	//computes factorial of BNum1, store in AFac
	while(counter > 1){
		counter--;
		AFac = AFac*counter;
	}
	
	pthread_mutex_unlock(&mut);
	return;
}


void *thread_B_func(){
	printf("THREAD B\n");
	
	
	printf("Input first number btwn 1 and 12: ");
	scanf("%d", &BNum1);
	printf("\n");
	if(BNum1 > 12)
	{
		printf("Number too big, modding by 12, adding 1\n");
		BNum1 = ((BNum1)%12) + 1;
		printf("New value is: %d\n", BNum1);
	}
	if(BNum1 == 0)
	{
		printf("0 is not between 1 and 12, making it 4\n");
		BNum1 = 4;
	}
	
	
	
	//wake A up
	pthread_mutex_unlock(&mut);
	
	
	printf("Input the string (less than 64 chars plz): ");
	//scanf("%s", str);
	fgets(str, sizeof(str), stdin);
	fgets(str, sizeof(str), stdin);//we have to do this 2 times because the previous scanf leaves the /n in the buffer, so the 1st read gets the /n, the 2nd gets the actual string

	printf("\n");

	return;
}



int main(int argc, char* argv[]){
	pthread_t thr_A;
	pthread_t thr_B;
	
	pthread_mutex_init(&mut, NULL);
	
	printf("THREAD START\n");
	pthread_mutex_lock(&mut);
//Create thread A
	pthread_create(&thr_A, NULL, thread_A_func, NULL);
//create thread B
	pthread_create(&thr_B, NULL, thread_B_func, NULL);


//Waits for thread A and B to finish
	pthread_join(thr_A, NULL);
	pthread_join(thr_B, NULL);	
	printf("THREAD OVER\n");
	
	
	printf("String is: %s\n", str);
	printf("Factorial of %d: %d.\n", BNum1, AFac);
	
	return 0;

}

