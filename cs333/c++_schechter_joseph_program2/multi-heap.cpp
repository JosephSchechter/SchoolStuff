#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;


typedef struct{
	int id;
	string subject;
	int date;
	string to;
	string from;
	int numLines;
	string * body;
	
	int alphabetPlace;
	int lengthPlace;
	int agePlace;	
}email;


void MaxHeapify(int a[], int size, int index, char method);
void BuildMaxHeap(int a[], int size, char method);
void Heapsort(int a[], int size, char method);

email * e;
int main(int argc, char* argv[])
{

	if(argc != 2){
		printf("Usage : ./multi_heap INPUTFILE");
		return 1; 
	}
	
	int numEmails = 0;
	
	//open the file
	string in (argv[1]);

/*	
	int numEmails = 0;
	string in = "input.txt";	
*/	
	
	
	
	
	ifstream input;
	input.open(in.data());
	if(input.fail())
	{
		cout << "\nNO file found, exiting";
		return 1;
	}
	else 
	{
		cout << "\nopen file success\n";
	}
	
//parse the file
	input >> numEmails;
	cout << "Number of emails is " << numEmails << endl;
	
	if(numEmails == 0)
	{
		cout << "no emails, exiting\n";
		return 0;
	}
	
	
	e = new email[numEmails];
	
	string garbage;
	
	for(int i = 0; i < numEmails; i++)
	{
		input >> garbage; //ID:
		input >> e[i].id;
		cout << "ID: " << e[i].id << endl;
		
		input >> garbage; //Subject:
		getline(input, e[i].subject);
		cout << "Subject: " <<e[i].subject << endl;
		
		input >> garbage; //date:
		input >> e[i].date;
		cout << "Date: " << e[i].date << endl;
		
		input >> garbage; //to:
		getline(input, e[i].to);
		cout << "To: " << e[i].to << endl;
		
		input >> garbage; //from:
		getline(input, e[i].from);
		cout << "From: " << e[i].from << endl;
		
		input >> garbage; //lines:
		input >> e[i].numLines;
		cout << "lines: " << e[i].numLines << endl;
		
		getline(input, garbage);
		
		//create an array of lines
		e[i].body =  new string[e[i].numLines];
		
		for(int j = 0; j < e[i].numLines; j++)
		{
			getline(input, e[i].body[j]);
			cout << e[i].body[j] << endl;
		}
	}
	input.close();
	
	//make 3 arrays
	int * alpHeap;
	alpHeap = new int[numEmails];
	int alpHeapCounter = numEmails;
	
	int * oldHeap;
	oldHeap = new int[numEmails];
	int oldHeapCounter = numEmails;
	
	
	int * sizeHeap;
	sizeHeap = new int[numEmails];
	int sizeHeapCounter = numEmails;
	
	
	for(int i = 0; i<numEmails; i++)
	{
		alpHeap[i] = i;
		e[i].alphabetPlace = i;
		
		oldHeap[i] = i;
		e[i].agePlace = i;
		
		sizeHeap[i] = i;
		e[i].lengthPlace = i;
	}
	
	//heapify the 3 arrays

//	cout <<"\nTest1\n";
	
	BuildMaxHeap(alpHeap, alpHeapCounter, 'a');
	BuildMaxHeap(oldHeap, oldHeapCounter, 'o');
	BuildMaxHeap(sizeHeap, sizeHeapCounter, 'l');

/*	
	for(int q = 0; q < numEmails; q++)
	{
		cout << "sizeheap " << sizeHeap[q] << endl;
	}
*/
	
	//user input phase
	
	
	string cmd1 = "words";
	string how = "words2";
	
	int swap;
	int otherheap1;
	int otherheap2;
	
	while(cmd1 != "QUIT")
	{
		cout << "\nEnter Command: ";
		cin >> cmd1;
		if(cmd1 == "QUIT")
		{
			cout << "\nExiting" << endl;
			//CLEANUP			
			return 0;
		}
		else if(cmd1 == "SORT")
		{
			//print the items in a sorted order, then re-heapify
			//cout << "You said sort" << endl;
			cin >> how;
			if(how == "ALPHABETICAL")
			{
				cout << "\nSORTING ALPHABETICALLY BY SUBJECT\n";
				Heapsort(alpHeap, alpHeapCounter, 'a');
				for(int q=alpHeapCounter-1; q >= 0; q--)
				{
					cout << "Subj:"<< e[alpHeap[q]].subject << endl;
					cout << "ID: "<< e[alpHeap[q]].id << endl;
					cout << "Date: " << e[alpHeap[q]].date << endl;
					cout << "To: " << e[alpHeap[q]].to << endl;
					cout << "From: " << e[alpHeap[q]].from << endl;
					cout << "Lines: " << e[alpHeap[q]].numLines << endl;
					cout << endl;
				}
				//rebuild the heap
				BuildMaxHeap(alpHeap, alpHeapCounter, 'a');
				cout << "\n\n"<< endl;
				
				
			}
			else if(how == "LONGEST")
			{
				cout << "\nSORTING BY LENGTH OF EMAIL\n";
				Heapsort(sizeHeap, sizeHeapCounter, 'l');
				for(int q=sizeHeapCounter-1; q>=0; q--)
				{
					cout << "Subj:"<< e[sizeHeap[q]].subject << endl;
					cout << "ID: "<< e[sizeHeap[q]].id << endl;
					cout << "Date: " << e[sizeHeap[q]].date << endl;
					cout << "To: " << e[sizeHeap[q]].to << endl;
					cout << "From: " << e[sizeHeap[q]].from << endl;
					cout << "Lines: " << e[sizeHeap[q]].numLines << endl;
					cout << endl;
				}
				//rebuild the heap
				BuildMaxHeap(sizeHeap, sizeHeapCounter, 'l');
				cout << "\n\n"<< endl;
				
			}
			else if(how == "OLDEST")
			{
				cout << "\nSORTING BY AGE OF EMAIL\n";
				Heapsort(oldHeap, oldHeapCounter, 'o');
				for(int q=oldHeapCounter-1; q>=0; q--)
				{
					cout << "Subj:"<< e[oldHeap[q]].subject << endl;
					cout << "ID: "<< e[oldHeap[q]].id << endl;
					cout << "Date: " << e[oldHeap[q]].date << endl;
					cout << "To: " << e[oldHeap[q]].to << endl;
					cout << "From: " << e[oldHeap[q]].from << endl;
					cout << "Lines: " << e[oldHeap[q]].numLines << endl;
					cout << endl;
				}
				//rebuild the heap
				BuildMaxHeap(oldHeap, oldHeapCounter, 'o');
				cout << "\n\n"<< endl;
				
			}
			else
			{
				cout << "\nunknown command, please try again";
			}
		}
		else if(cmd1 == "EXTRACT")
		{
			//remove the top item and decriment size (also remove it from the other lists)
			//cout << "You said extract" << endl;
			cin >> how;
			if(how == "ALPHABETICAL")
			{
				cout << "THE BIGGEST (ALPHABETICAL) SUBJECT IS: " <<endl;
				cout << "Subj:"<< e[alpHeap[0]].subject << endl;
				cout << "ID: "<< e[alpHeap[0]].id << endl;
				cout << "Date: " << e[alpHeap[0]].date << endl;
				cout << "To: " << e[alpHeap[0]].to << endl;
				cout << "From: " << e[alpHeap[0]].from << endl;
				cout << "Lines: " << e[alpHeap[0]].numLines << endl;
				cout << endl;
				
				swap = alpHeap[0];
				
				e[alpHeap[0]].alphabetPlace = alpHeap[alpHeapCounter-1];
				alpHeap[0] = alpHeap[alpHeapCounter-1];
				e[alpHeap[alpHeapCounter-1]].alphabetPlace = swap;
				alpHeap[alpHeapCounter-1] = swap;
				alpHeapCounter--;
				BuildMaxHeap(alpHeap, alpHeapCounter, 'a');
				
				
				otherheap1 = e[swap].lengthPlace; //sizeheap
				otherheap2 = e[swap].agePlace; //oldheap
				
				swap = sizeHeap[otherheap1];
				
				e[sizeHeap[otherheap1]].lengthPlace = sizeHeap[sizeHeapCounter-1];
				sizeHeap[otherheap1] = sizeHeap[sizeHeapCounter-1];
				e[sizeHeap[sizeHeapCounter-1]].lengthPlace = swap;
				sizeHeap[sizeHeapCounter-1] = swap;
				sizeHeapCounter--;
				BuildMaxHeap(sizeHeap, sizeHeapCounter, 'l');
				
				swap = oldHeap[otherheap2];
				
				e[oldHeap[otherheap2]].agePlace = oldHeap[oldHeapCounter-1];
				oldHeap[otherheap2] = oldHeap[oldHeapCounter-1];
				e[oldHeap[oldHeapCounter-1]].agePlace = swap;
				oldHeap[oldHeapCounter-1] = swap;
				oldHeapCounter--;
				BuildMaxHeap(oldHeap, oldHeapCounter, 'o');
				
				
			
			}
			else if(how == "LONGEST")
			{
				cout << "THE LONGEST EMAIL IS: " <<endl;
				cout << "Subj:"<< e[sizeHeap[0]].subject << endl;
				cout << "ID: "<< e[sizeHeap[0]].id << endl;
				cout << "Date: " << e[sizeHeap[0]].date << endl;
				cout << "To: " << e[sizeHeap[0]].to << endl;
				cout << "From: " << e[sizeHeap[0]].from << endl;
				cout << "Lines: " << e[sizeHeap[0]].numLines << endl;
				cout << endl;
			
			
			
				swap = sizeHeap[0];
				
				e[sizeHeap[0]].lengthPlace = sizeHeap[sizeHeapCounter-1];
				sizeHeap[0] = sizeHeap[sizeHeapCounter-1];
				e[sizeHeap[sizeHeapCounter-1]].lengthPlace = swap;
				sizeHeap[sizeHeapCounter-1] = swap;
				sizeHeapCounter--;
				BuildMaxHeap(sizeHeap, sizeHeapCounter, 'l');
				
				
				otherheap1 = e[swap].alphabetPlace; //alpheap
				otherheap2 = e[swap].agePlace; //oldheap
				
				swap = alpHeap[otherheap1];
				
				e[alpHeap[otherheap1]].alphabetPlace = alpHeap[alpHeapCounter-1];
				alpHeap[otherheap1] = alpHeap[alpHeapCounter-1];
				e[alpHeap[alpHeapCounter-1]].alphabetPlace = swap;
				alpHeap[alpHeapCounter-1] = swap;
				alpHeapCounter--;
				BuildMaxHeap(alpHeap, alpHeapCounter, 'a');
				
				swap = oldHeap[otherheap2];
				
				e[oldHeap[otherheap2]].agePlace = oldHeap[oldHeapCounter-1];
				oldHeap[otherheap2] = oldHeap[oldHeapCounter-1];
				e[oldHeap[oldHeapCounter-1]].agePlace = swap;
				oldHeap[oldHeapCounter-1] = swap;
				oldHeapCounter--;
				BuildMaxHeap(oldHeap, oldHeapCounter, 'o');
			
			
			
			
			}
			else if(how == "OLDEST")
			{
				cout << "THE OLDEST EMAIL IS: " <<endl;
				cout << "Subj:"<< e[oldHeap[0]].subject << endl;
				cout << "ID: "<< e[oldHeap[0]].id << endl;
				cout << "Date: " << e[oldHeap[0]].date << endl;
				cout << "To: " << e[oldHeap[0]].to << endl;
				cout << "From: " << e[oldHeap[0]].from << endl;
				cout << "Lines: " << e[oldHeap[0]].numLines << endl;
				cout << endl;
				
				
				
				swap = oldHeap[0];
				
				e[oldHeap[0]].agePlace = oldHeap[oldHeapCounter-1];
				oldHeap[0] = oldHeap[oldHeapCounter-1];
				e[oldHeap[oldHeapCounter-1]].agePlace = swap;
				oldHeap[oldHeapCounter-1] = swap;
				oldHeapCounter--;
				BuildMaxHeap(oldHeap, oldHeapCounter, 'o');
				
				
				
				
				otherheap1 = e[swap].alphabetPlace; //alpheap
				otherheap2 = e[swap].lengthPlace; //sizeheap
				
				
				
				
				
				swap = alpHeap[otherheap1];
				
				e[alpHeap[otherheap1]].alphabetPlace = alpHeap[alpHeapCounter-1];
				alpHeap[otherheap1] = alpHeap[alpHeapCounter-1];
				e[alpHeap[alpHeapCounter-1]].alphabetPlace = swap;
				alpHeap[alpHeapCounter-1] = swap;
				alpHeapCounter--;
				BuildMaxHeap(alpHeap, alpHeapCounter, 'a');
				



				
				swap = sizeHeap[otherheap2];
				
				e[sizeHeap[otherheap2]].lengthPlace = sizeHeap[sizeHeapCounter-1];
				sizeHeap[otherheap2] = sizeHeap[sizeHeapCounter-1];
				e[sizeHeap[sizeHeapCounter-1]].lengthPlace = swap;
				sizeHeap[sizeHeapCounter-1] = swap;
				sizeHeapCounter--;
				BuildMaxHeap(sizeHeap, sizeHeapCounter, 'l');
			}
			else
			{
				cout << "\nunknown command, please try again";
			}
		}
		else if(cmd1 == "REPORT")
		{
			//cout << "You said report" << endl;
			cin >> how;
			if(how == "ALPHABETICAL")
			{
				cout << "THE BIGGEST (ALPHABETICAL) SUBJECT IS: " <<endl;
				cout << "Subj:"<< e[alpHeap[0]].subject << endl;
				cout << "ID: "<< e[alpHeap[0]].id << endl;
				cout << "Date: " << e[alpHeap[0]].date << endl;
				cout << "To: " << e[alpHeap[0]].to << endl;
				cout << "From: " << e[alpHeap[0]].from << endl;
				cout << "Lines: " << e[alpHeap[0]].numLines << endl;
				cout << endl;
			}
			else if(how == "LONGEST")
			{
				cout << "THE LONGEST EMAIL IS: " <<endl;
				cout << "Subj:"<< e[sizeHeap[0]].subject << endl;
				cout << "ID: "<< e[sizeHeap[0]].id << endl;
				cout << "Date: " << e[sizeHeap[0]].date << endl;
				cout << "To: " << e[sizeHeap[0]].to << endl;
				cout << "From: " << e[sizeHeap[0]].from << endl;
				cout << "Lines: " << e[sizeHeap[0]].numLines << endl;
				cout << endl;
			}
			else if(how == "OLDEST")
			{
				cout << "THE OLDEST EMAIL IS: " <<endl;
				cout << "Subj:"<< e[oldHeap[0]].subject << endl;
				cout << "ID: "<< e[oldHeap[0]].id << endl;
				cout << "Date: " << e[oldHeap[0]].date << endl;
				cout << "To: " << e[oldHeap[0]].to << endl;
				cout << "From: " << e[oldHeap[0]].from << endl;
				cout << "Lines: " << e[oldHeap[0]].numLines << endl;
				cout << endl;
			}
			else
			{
				cout << "\nunknown command, please try again";
			}
		}
		else
		{
			cout << "\nunknown command, please try again";
		}
		
		if(oldHeapCounter == 0) //IF ONE IS 0, THEY ALL ARE 0 LOLOOOL
		{
			cout <<"\nYOU HAVE REACHED THE END OF EMAILS, EXITING\n";
			return 0;
		}
		
	}
	
	
	
	
	return 0;
}


void MaxHeapify(int a[], int size, int index, char method)
{
	int left = index*2 + 1;//left child
	int right = index*2 + 2;//right child
	
	int largest;
	
	int temp;
	
//	cout << "\nin maxheapify\n";
	
	switch(method)
	{
		case 'a'://alphabetical
			if((left <= size-1) && (e[a[left]].subject > e[a[index]].subject))
			{
				largest = left;
			}
			else
			{
				largest = index;
			}
			
			if((right <= size-1) && (e[a[right]].subject > e[a[largest]].subject))
			{
				largest = right;
			}
			
			if(largest != index)
			{
				temp = a[index];
				e[a[index]].alphabetPlace = a[largest];
				a[index] = a[largest];
				e[a[largest]].alphabetPlace = temp;
				a[largest] = temp;
				
				
				MaxHeapify(a, size, largest, method);
			}
			break;
		case 'l': //longest
//			cout << "\nshit1\n";
			if((left <= size-1) && (e[a[left]].numLines > e[a[index]].numLines))
			{
				largest = left;
			}
			else
			{
				largest = index;
			}
//			cout << "\nshit2\n";
			if((right <= size-1) && (e[a[right]].numLines > e[a[largest]].numLines))
			{
				largest = right;
			}
//			cout << "\nshit3\n";
			if(largest != index)
			{
				temp = a[index];
				e[a[index]].lengthPlace = a[largest];
				a[index] = a[largest];
				e[a[largest]].lengthPlace = temp;
				a[largest] = temp;
				
				
				MaxHeapify(a, size, largest, method);
			}
			break;
		case 'o': //oldest
			if((left <= size-1) && (e[a[left]].date > e[a[index]].date))
			{
				largest = left;
			}
			else
			{
				largest = index;
			}
			
			if((right <= size-1) && (e[a[right]].date > e[a[largest]].date))
			{
				largest = right;
			}
			
			if(largest != index)
			{
				temp = a[index];
				e[a[index]].agePlace = a[largest];
				a[index] = a[largest];
				e[a[largest]].agePlace = temp;
				a[largest] = temp;
				
				
				MaxHeapify(a, size, largest, method);
			}
			break;
	}
}



void BuildMaxHeap(int a[], int size, char method)
{
//	cout << "\nbuildmaxheap\n";
	for(int i = size/2 - 1; i >= 0; i--)
	{
//		cout << "call maxheapify" << i <<endl;
		MaxHeapify(a, size, i, method);
	}
}


void Heapsort(int a[], int size, char method)
{
	BuildMaxHeap(a, size, method);
	int temp;
	for(int i = size-1; i >= 1; i--)
	{
		switch(method)
		{
			case 'a'://alphabetical
				temp = a[0];
				e[a[0]].alphabetPlace = a[i];
				a[0] = a[i];
				e[a[i]].alphabetPlace = temp;
				a[i] = temp;
				break;
			case 'l': //longest
				temp = a[0];
				e[a[0]].lengthPlace = a[i];
				a[0] = a[i];
				e[a[i]].lengthPlace = temp;
				a[i] = temp;
				break;
			case 'o': //oldest
				temp = a[0];
				e[a[0]].agePlace = a[i];
				a[0] = a[i];
				e[a[i]].agePlace = temp;
				a[i] = temp;
				break;
		}
				
		
		size = size-1;
		
		MaxHeapify(a, size, 0, method);
	}
}

