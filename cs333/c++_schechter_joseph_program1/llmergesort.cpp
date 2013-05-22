#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "List.h"
using namespace std;

int main (int argc, char *argv[]) {

	List *inputList = new List();
	int in = 0;
	int test = 0;
	
	while (scanf("%d", &in) == 1)
	{
		test = inputList->insert(in);
		if(test == -1)
		{
			cout << "Memory allocation problem, exiting";
			return 0;
		}
	}
	
	//inputList->show();

/*
	int num = inputList->num_elements;
	cout << num;

	if(num == 0){
		printf("\nYou put in no numbers, exiting\n");
		return(0);
	}

	if(num == 1){
		cout << inputList->list_head->data;
	}

	
	//create an array of the pointers to items in the list
	for(int i = 0; i<num; i++){
	}

	//perform mergesort on the pointers of the array

	//once it is sorted, make a new list and change the on-data pointers to order them correctly

	//print out the numbers in correct order

	
*/	
	return 0;
}
