#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <time.h>


//define new syscall 
#define __NR_my_xtime 299

int main(void)
{
	struct timespec ret;
	syscall(__NR_my_xtime, ret);


	printf("\nsuccess!\n");
	return 0;
	
	
}
