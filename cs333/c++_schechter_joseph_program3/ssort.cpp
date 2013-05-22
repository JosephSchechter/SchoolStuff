#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define CHARS 53



using namespace std;

typedef struct fullWord{
	string str;
	int length;
	fullWord * next;
} fullWord;

typedef struct{
	fullWord * head;
	int count;//number of words
	void insert(fullWord f){
		fullWord *new_word = new fullWord;
		new_word->str = f.str;
		new_word->length = f.length;
		
		if(head == NULL)
		{
			head = new_word;
		}
		else
		{
			new_word->next = head;
			head = new_word;
		}
		count++;
	}
} wordList;

void stringSort(fullWord array[], int start, int end, int place);

wordList wl;

int main(int argc, char* argv[])
{
//get input from user into linked lists
	wl.count = 0;
	wl.head = NULL;
//cout << "test1" << endl;
	char c = 'a';
	fullWord fw;
	fw.length = 0;
	fw.str = "";
	fw.next = NULL;
	while((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			if(fw.length != 0)
			{
				wl.insert(fw);
				fw.length = 0;
				fw.str = "";
				fw.next = NULL;
			}
		}
		else
		{
			fw.str = fw.str + c;
			fw.length = fw.length +1;		
		}
	}
	if(fw.length != 0)
	{
		wl.insert(fw);
	}
	
	
//	cout << "total number of words: " << wl.count << endl;
	fullWord *ptr = wl.head;
/*	while(ptr != NULL)
	{
		cout << ptr->str << " length: " << ptr->length << endl;
		ptr = ptr->next;		
	}
*/	
//	cout << "~~done reading~~" << endl;
	
	//convert into a big array
	fullWord * myArray;
	myArray = new fullWord[wl.count];
	if(wl.count == 0)
	{
		cout << "no words in this list, exiting" << endl;
		return 0;
	}
	ptr = wl.head;
	for(int i = 0; i<wl.count; i++)
	{
		myArray[i].str = ptr->str;
		myArray[i].length = ptr->length;
		ptr = ptr->next;
//		cout << myArray[i].str << " length: " << myArray[i].length << endl;
	}
	
//sort strings
	int charPlace = 0; //the character in the word we are looking at 
	int start = 0;		//where in the array we are sorting
	int end = wl.count - 1;	//^^
	stringSort(myArray, start, end, charPlace);
	
	//print out the newly sorted array
	
//	cout << "\n\n~~~FINAL LIST~~~" << endl;
	
	for(int i = 0; i<wl.count; i++)
	{
		cout << myArray[i].str << endl;
	}
	
	delete[] myArray;
}


//0 = no character, the 1st non-character, it has just ended
//1-26 == a-z
//27-52 == A-Z
//53 total spots

void stringSort(fullWord array[], int start, int end, int place)
{
int numberOfDifferentStartLetters = 0;


//cout << endl;
//cout << "test2: start: " << start << " end: " << end << " place: " << place<< endl;
	if(start == end) //single word, no need to order
	{
		return;
	}
	int countingArray[CHARS];	//count each character (like counting sort)
	int trackingArray[CHARS];	//which place in the FW array to put the next word with that letter
	for(int j = 0; j < CHARS; j++) //initializing the arrays
	{
		countingArray[j] = 0;
		trackingArray[j] = 0;
	}
	
	for(int i = start; i <= end; i++)	//get the counts of all the chars in a single position
	{
		if(array[i].length == place) //the 1st non-character
		{
			countingArray[0] = countingArray[0] + 1;
		}
		else if((array[i].str[place] >= 65) && (array[i].str[place] <= 90))	//capital letters A-Z
		{
			countingArray[array[i].str[place] - 38] = countingArray[array[i].str[place] - 38] + 1;	//38 brings A to cA[27]
			if(countingArray[array[i].str[place] - 38] == 1)
			{
				numberOfDifferentStartLetters++;
			}
		}
		else if((array[i].str[place] >= 97) && (array[i].str[place] <= 122))	//lower case a-z
		{
			countingArray[array[i].str[place] - 96] = countingArray[array[i].str[place] - 96] + 1;	//96 brings a to cA[1]
			if(countingArray[array[i].str[place] - 96] == 1)
			{
				numberOfDifferentStartLetters++;
			}
		}
	}
	
	
	//the places in myarray where each substring starting with X start
	trackingArray[0] = countingArray[0];
	for(int j = 1; j<CHARS; j++)
	{
		trackingArray[j] = trackingArray[j-1] + countingArray[j];
	}

	
	//backup of array[]
	fullWord * arrayB;
	arrayB = new fullWord[(end+1)-start];
	for(int j = 0; j<(end+1)-start; j++)
	{
		arrayB[j].str = array[start+j].str;
		arrayB[j].length = array[start+j].length;
	}
	
//cout << "test3" << endl;	
	//modifying the array[] and putting them in order according to that single letter we are comparing
	//by going through the backup and putting things in the right spot in the array[]
	for(int i = 0; i < (end+1)-start; i++)
	{
		if(arrayB[i].length == place)//the 1st non-character
		{
			array[start + (trackingArray[0]-1)].str = arrayB[i].str;
			array[start + (trackingArray[0]-1)].length = arrayB[i].length;
			trackingArray[0] = trackingArray[0] - 1;
		}
		else if((arrayB[i].str[place] >= 97) && (arrayB[i].str[place] <= 122))	//lower case a-z
		{
			array[start + (trackingArray[arrayB[i].str[place]- 96] - 1)].str = arrayB[i].str;
			array[start + (trackingArray[arrayB[i].str[place]- 96] - 1)].length = arrayB[i].length;
			trackingArray[arrayB[i].str[place]- 96] = trackingArray[arrayB[i].str[place]- 96] -1;
		}
		else if((arrayB[i].str[place] >= 65) && (arrayB[i].str[place] <= 90))	//capital letters A-Z
		{
			array[start + (trackingArray[arrayB[i].str[place]- 38] - 1)].str = arrayB[i].str;
			array[start + (trackingArray[arrayB[i].str[place]- 38] - 1)].length = arrayB[i].length;
			trackingArray[arrayB[i].str[place]- 38] = trackingArray[arrayB[i].str[place]- 38] -1;
		}	
	}
	
/*	
cout << "test4" << endl;
cout << "' '  = " << countingArray[0] << " , ";
for(int i =1; i<27; i++)
{
	cout << (char)(i+96) << " = " << countingArray[i] << " , ";
}
for(int i = 27; i<CHARS; i++)
{
	cout << (char)(i+38) << " = " << countingArray[i] << " , ";;
}
cout << endl;
*/

/*
cout << "~~~partial list~~" << endl;
for(int i = start; i <= end; i++)
{
	cout << array[i].str << endl;
}
*/

/*
cout << endl;
cout << "~~~Tracking Array~~~" << endl;
cout << "' '  = " << trackingArray[0] << " , ";
for(int i =1; i<27; i++)
{
	cout << (char)(i+96) << " = " << trackingArray[i] << " , ";
}
for(int i = 27; i<CHARS; i++)
{
	cout << (char)(i+38) << " = " << trackingArray[i] << " , ";;
}
cout << endl;
*/


	
/*	
//cout << "\nNUMber of dif start letters = " << numberOfDifferentStartLettters << endl;
int difCounter = numberOfDifferentStartLetters;
//int curTrack = trackingArray[0];
int t = 1;
//int nextTrack = trackingArray[t];
int myStart = start + countingArray[0];
int myEnd;
while(difCounter > 0)
{
	if(countingArray[t] > 0)
	{
		difCounter--;
		myEnd = myStart + countingArray[t] - 1;
//		stringSort(array, myStart, myEnd, place+1);
		t++;
		myStart = myStart + countingArray[t];
	}
	else
	{
		t++;
	}
}

 */


	int newStart = start + countingArray[0];	//those words ended and wont be read again
	int z = newStart;
	int letterSpot = 1;
	while(z < end) //if z ever reaches 
	{
		while(countingArray[letterSpot] == 0)
		{
			letterSpot++; //get to a letter that isn't counted 0 times
		}
		//cout << "start: " << z << " , end: " << z + (countingArray[letterSpot]-1) << " , Place " << place+1 << endl;
		stringSort(array, z, z + (countingArray[letterSpot]-1), place + 1);
		z = z + countingArray[letterSpot];
		letterSpot++;
	}
	
	delete [] arrayB;
	
	
	
}













