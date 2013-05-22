#include <stdio.h>
#define MAX_ELEMENTS 10000


int data[MAX_ELEMENTS];


void recsort(int * array, int size){
	if(size == 1){
		return;
	}
	//sort the 0 to A-1 array
	recsort(array, size-1);
	
	//place the last item into its correct position
	
	int key = array[size-1];
	int j = size-2;
	while(array[j]>key && j>=0)
	{
		array[j+1] = array[j];
		j--;
	}
	array[j+1] = key;

	return;
}


int main()
{

//Take in data into a MAX_ELEMENT size array
	int i;
	int n = 0;
	
	//printf("\nBEGIN INPUT OF NUMBERS, END WITH A NON-NUMBER CHAR\n");
	
	
	while (scanf("%d", &data[n]) == 1)
	{
		n++;
		if(n>=MAX_ELEMENTS){
//			printf("\nREACHED LIMIT, BREAKING READ LOOP\n");
			break;
		}
	}

/*	
//Print out what the user input
	printf("\nYou put in %d values to sort\n", n);
	for (i = 0; i < n; i++){
		printf("%d\n", data[i]);
	}
*/

// no items	
	if(n == 0){
		printf("\nYou put in no numbers, exiting\n");
		return(0);
	}

// 1 item
	if(n == 1){
//		printf("\nYou put in one number.\n");
//		printf("\nYOUR SORTED ARRAY:\n");
		printf("%d\n", data[0]);
//		printf("\nExiting\n");		
		return(0);
	}
	
	recsort(data, n);
	
	
//	printf("\nYOUR SORTED ARRAY:\n");
	for (i = 0; i < n; i++){
		printf("%d\n", data[i]);
	}
	
//	printf("\nExiting\n");
	
	return(0);
	
	
}

