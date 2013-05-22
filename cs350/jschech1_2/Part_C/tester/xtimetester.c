#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>

//#define N 100
//#define N 1000
#define N 10
#define LENGTH 512



struct timeval gtodTimes[N];
char procClockTimes[N][LENGTH];



int main(){
	int i;
	printf("\n");
	
	for( i=0; i < N; i++)
	{
		FILE * my_xtime = fopen("/proc/myxtime", "r");
		gettimeofday(&gtodTimes[i], 0);
		fgets(procClockTimes[i], LENGTH, my_xtime);
		
		printf("Time of Day: %ld %ld \t\t ProcClock:  %s\n", gtodTimes[i].tv_sec, gtodTimes[i].tv_usec*1000, &procClockTimes[i]);
		fclose(my_xtime);
	}

	return 0;
}

