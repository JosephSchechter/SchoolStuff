#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>

#define ALP 26

using namespace std;

//letter node
typedef struct huffNode{
	char letter;
	int freq;
	string sBin;//binary string representation
	//for the linked list part
	huffNode *next;
	huffNode *prev;
	
	//for the tree part (children+parent)
	huffNode *leftC;
	huffNode *rightC;
	huffNode *parent;
	
} huffNode;

//letter linked list
typedef struct{
	huffNode * head;
	int count;//number of nodes
	void insert(char l, int f){
		huffNode *new_node = new huffNode;
		new_node->freq = f;
		new_node->letter = l;
		new_node->sBin = "";
		new_node->leftC = NULL;
		new_node->rightC = NULL;
		new_node->parent = NULL;
		
		
		if(head == NULL)//empty list
		{
			head = new_node;
			new_node->next = NULL;
			new_node->prev = NULL;
			
		}
		else//add it to the front of the list
		{
			head->prev = new_node;
			new_node->next = head;
			new_node->prev = NULL;
			head = new_node;
		}
		count++;
	}
} huffList;






//word node
typedef struct fullWord{
	string alpWord;
	double length; //# of alphabetical characters
	fullWord * next;
	
	string hufWord;
	double weight; //length of huffman encoding
	double value; //sum of letter values
	double vpw; //value per weight
	
} fullWord;



//word linked list
typedef struct{
	fullWord * head;
	int count;//number of words
	void insert(fullWord f){
		fullWord *new_word = new fullWord;
		new_word->alpWord = f.alpWord;
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


void stringFunc(huffNode * h, char dir, string array[]);


int main(int argc, char* argv[])
{

	//correct # of args
	if(argc != 4)
	{
		cout << "correct usage: ./huffman -{d/g} <knapsack_size> <knapsack_file>" << " exiting" << endl;
		return 0;
	}
	
	char howSolve = 'x'; //d or g
	
	
	
	//correct -{dg}
	if(strlen(argv[1]) != 2)	//length of 2
	{
		cout << "have it be either \"-d\" or \"-g\", nothing else, exiting" << endl;
		return 0;
	}
	if(argv[1][0] != '-')		//starts with -
	{
		cout << "have it be either \"-d\" or \"-g\", nothing else, exiting" << endl;
		return 0;
	}
	if(argv[1][1] == 'd')		//d
	{
//		cout << "dyanmic 0-1 knapsack" << endl;
		howSolve = 'd';
	}
	else if(argv[1][1] == 'g')	//g
	{
//		cout << "greedy fractional knapsack" << endl;
		howSolve = 'g';
	}
	else
	{
		cout << "have it be either \"-d\" or \"-g\", nothing else, exiting" << endl;
		return 0;
	}
	
	//get the knapsack size
	int knapsackSizeInt = atoi(argv[2]);
	double knapsackSize = knapsackSizeInt;
//	cout << "knapsackSize is " << knapsackSize << endl;
	
	//get the output file
	FILE *outFile = fopen(argv[3], "w");
	if (outFile == 0)
	{
		cout << "cant open file, exiting" << endl;
		return 0;
	}
	else
	{
//		cout << "success opening file" << endl;
	}

	
	




	
	int alpCount[26];	//a = [0], z = [25]
	string binaryRepresentation[26];	//string rep of binary rep of the huffman encoded letters
	int totalChars = 0;
	char alp[26]; //just contains the letters a-z, used for keeping track of the other arrays
	
	for(int i = 0; i<26; i++)
	{
		alpCount[i] = 0;
		binaryRepresentation[i] = "";
		alp[i] = i + 97;
	}
	
	
	
	
	
	//getting input
	
	wordList wl;
	wl.count = 0;
	wl.head = NULL;
	fullWord fw;
	fw.length = 0;
	fw.alpWord = "";
	fw.next = NULL;
	
	char c = 'a';
	while((c = getchar()) != EOF)
	{
		if (c == '\n') 
		{
			if(fw.length != 0)
			{
				wl.insert(fw);
				fw.length = 0;
				fw.alpWord = "";
				fw.next = NULL;
			}
			//cout << "NEWLINE" << endl;
		}
		else	//finds a letter a-z
		{
			if((c >= 97) && (c <= 122))
			{
			//cout << c << endl;
				alpCount[(c-97)]++;
				totalChars++;
				
				
				//add letters until the word ends with /n or EOF
				fw.alpWord = fw.alpWord + c;
				fw.length = fw.length + 1;
			}
			else
			{
				cout << "\nweird character in input file, exiting";
				return 0;
			}
		}
	}
	if(fw.length != 0)
	{
		wl.insert(fw);
	}
	
	
	//sort by freq, large to small (sorting 2 arrays, the letters and the freq array)
	//do this so we can put them in backwards
	//always 26 letters so constant time
	for(int i =0; i<26; i++)
	{
		for(int j =0; j<i; j++)
		{
			if(alpCount[i] > alpCount[j])
			{
				int alpCountTemp = alpCount[i];
				char alpTemp = alp[i];
				
				
				alpCount[i] = alpCount[j];
				alp[i] = alp[j];
				
				
				alpCount[j] = alpCountTemp;
				alp[j] = alpTemp;
			}
		}
	}

/*	
	//printing out letters and count
	cout << "Total Characters: " << totalChars << endl;
	for(int i = 0; i<26; i++)
	{
		//cout << (char)(i+97) << ": " << alpCount[i] << endl;
		cout << alp[i] << ": " << alpCount[i] << endl;
	}
*/
	
	
	
	//put them into the linked list
	huffList hl;
	hl.count = 0;
	hl.head = NULL;	
	for(int i = 0; i <26; i++)
	{
		hl.insert(alp[i], alpCount[i]);
	}
	
/*	
	//check
	cout << "\ncheck\n";
	huffNode *tempNode = hl.head;
	for(int i =0; i<26; i++)
	{
		cout << tempNode->letter << ": " << tempNode->freq << endl;
		tempNode = tempNode->next;
		
	}
*/

	
	//build the huffman tree in the ll
	huffNode *new_node;
	huffNode *position;
//	cout <<"\ntest1\n";
	while(hl.count > 1)
	{
/*	
		//check2
		cout << "\ncheck2\n";
		tempNode = hl.head;
		for(int i =0; i<hl.count; i++)
		{
			cout << tempNode->letter << ": " << tempNode->freq << endl;
			tempNode = tempNode->next;
			
		}
*/		
	
	
//		cout <<"\ntest2\n";
		
		//Create new node
		new_node = new huffNode;
		new_node->letter = '-';//not a real letter
		new_node->prev = NULL;
		new_node->next = NULL;
		
//		cout <<"\ntest2.1\n";
		
		//Remove first node and make it left subtree
		new_node->leftC = hl.head;
		hl.head->parent = new_node;
		hl.head = hl.head->next;
		
//		cout <<"\ntest2.2\n";
		
		//Remove second node and make it right subtree
		new_node->rightC = hl.head;
//		cout <<"\ntest2.2.1\n";
		hl.head->parent = new_node;
//		cout <<"\ntest2.2.2\n";
		hl.head = hl.head->next;
//		cout <<"\ntest3\n";
		
		
		//Frequency of new node equals sum of frequency of left and right children
		new_node->freq = new_node->rightC->freq + new_node->leftC->freq;
		
		
//		cout <<"\ntest4\n";
		
		
		
		
		
		
		//Place new node back into list into sorted position
		
		if(hl.head == NULL)//there were only 2 items in the list, now there are 0, put that 1 parent in
		{
			hl.head = new_node;
		}
		else//there is at least 1 item to search through to see where the new node needs to be put
		{
			position = hl.head;
//			cout <<"\ntest5\n";
			
			while(position != NULL)
			{
				if(position->freq > new_node->freq)
				{
					new_node->next = position;
					new_node->prev = position->prev;
					position->prev = new_node;					
					if(new_node->prev == NULL)
					{
						hl.head = new_node;
					}
					else if(hl.head == position)
					{
						hl.head = new_node;
					}
					else
					{
						new_node->prev->next = new_node;
					}
					
					position = NULL;
				}
				else //new_node is bigger or equal to current node position is looking at
				{
					if(position->next == NULL)//if its the last in the list, put the new node at the end of list
					{
						position->next = new_node;
						new_node->prev = position;
						position = NULL;
					}
					else//move to next node
					{
						position = position->next;
					}
				}
			}
		}
		
		
		
//		cout <<"\nloop\n";
		hl.count--;
//		cout << "hl count: " << hl.count<<endl;
		new_node = NULL;
	
	}
	
	
	
//	cout << "out";

/*
	cout << "\ncheck2\n";
	tempNode = hl.head;
	for(int i =0; i<hl.count; i++)
	{
		cout << tempNode->letter << ": " << tempNode->freq << endl;
		tempNode = tempNode->next;
		
	}
*/	
	
	
	
	//figure out the binary representation for the ll nodes
	//traverse the tree, adding a "0" if it goes left and adding a 1 if right
	//put the strings in the binaryRepresentation array
	stringFunc(hl.head, 'o', binaryRepresentation);
	
	//sort the arrays alphabetically
	for(int i =0; i<26; i++)
	{
		for(int j =0; j<i; j++)
		{
			if(alp[i] < alp[j])
			{
				int alpCountTemp = alpCount[i];
				char alpTemp = alp[i];
				
				
				alpCount[i] = alpCount[j];
				alp[i] = alp[j];
				
				
				alpCount[j] = alpCountTemp;
				alp[j] = alpTemp;
			}
		}
	}
	
	
	

	//At this point in the code, we have the letters [alp] and their [binaryrepresentation] sorted a-z
	
	
	//put all words into an array from the wl
	fullWord *ptr = wl.head;
	fullWord * wordArray;
	wordArray = new fullWord[wl.count];
	if(wl.count == 0)
	{
		cout << "no words in this list, exiting" << endl;
		return 0;
	}
	ptr = wl.head;
	for(int i = 0; i<wl.count; i++)
	{
		wordArray[i].alpWord = ptr->alpWord;
		wordArray[i].length = ptr->length;
		ptr = ptr->next;
		
		//testing
//		cout << wordArray[i].alpWord << " length: " << wordArray[i].length << endl;
	}
	
	
	//create a value array of what each letter is worth
	int valueArray[26]; //va[0] is a's value (1), va[25] is z's value (26)
	for(int i = 0; i<26; i++)
	{
		valueArray[i] = i+1;
	}
	
	
	//now we need to add the full binary representation to the words, as well as add the length of the binary string to get the weight of the word
	for(int i = 0; i<wl.count; i++)//go through each word
	{
		wordArray[i].hufWord = "";
		wordArray[i].value = 0;
		for(int j = 0; j< wordArray[i].length; j++)//go through each letter of a word
		{
			wordArray[i].hufWord = wordArray[i].hufWord + binaryRepresentation[wordArray[i].alpWord[j] - 97];
			wordArray[i].value = wordArray[i].value + valueArray[wordArray[i].alpWord[j] - 97];
		}
		wordArray[i].weight = wordArray[i].hufWord.length();
		wordArray[i].vpw = wordArray[i].value / wordArray[i].weight;
	
		/*	
		cout << "String: " << wordArray[i].alpWord << endl;
		cout << "Length: " << wordArray[i].length << endl;
		cout << "Hufenc: " << wordArray[i].hufWord << endl;
		cout << "weight: " << wordArray[i].weight << endl;
		cout << "vpw: " << wordArray[i].vpw << endl;
		cout << "\n";
		*/
		
	}
	
	//now sort the wordArray by vpw in descending order
	for(int i =0; i<wl.count; i++)
	{
		for(int j =0; j<i; j++)
		{
			//if(alpCount[i] > alpCount[j])
			if(wordArray[i].vpw > wordArray[j].vpw)
			{
				//int alpCountTemp = alpCount[i];
				//char alpTemp = alp[i];
				string alpWordTemp = wordArray[i].alpWord;
				double lengthTemp = wordArray[i].length;
				string hufWordTemp = wordArray[i].hufWord;
				double valueTemp = wordArray[i].value;
				double weightTemp = wordArray[i].weight;
				double vpwTemp = wordArray[i].vpw;
				
				
				//alpCount[i] = alpCount[j];
				//alp[i] = alp[j];
				wordArray[i].alpWord = wordArray[j].alpWord;
				wordArray[i].length = wordArray[j].length;
				wordArray[i].hufWord = wordArray[j].hufWord;
				wordArray[i].value = wordArray[j].value;
				wordArray[i].weight = wordArray[j].weight;
				wordArray[i].vpw = wordArray[j].vpw;
				
				
				//alpCount[j] = alpCountTemp;
				//alp[j] = alpTemp;
				wordArray[j].alpWord = alpWordTemp;
				wordArray[j].length = lengthTemp;
				wordArray[j].hufWord = hufWordTemp;
				wordArray[j].value = valueTemp;
				wordArray[j].weight = weightTemp;
				wordArray[j].vpw = vpwTemp;
				
			}
		}
	}
/*	
	//print out words sorted by vpw
	for(int i = 0; i<wl.count; i++)//go through each word
	{
		cout << "String: " << wordArray[i].alpWord << endl;
		cout << "Length: " << wordArray[i].length << endl;
		cout << "Value: " << wordArray[i].value << endl;
		cout << "Hufenc: " << wordArray[i].hufWord << endl;
		cout << "weight: " << wordArray[i].weight << endl;
		cout << "vpw: " << wordArray[i].vpw << endl;
		cout << "\n";
	}
*/	
//	cout << "split problem" << endl;
	//fractional knapsack (greedy)
	if(howSolve == 'g')
	{
//		cout << "in g" << endl;
		int wordPlace = 0; //place in the list of words, starting at highest vpw, (wordArray[0])
		double filledSack = 0;//number of 1's or 0's in the sack
		double sackValue = 0;	//the value of the words in the sack
		
		//we have not reached the end of the array and there is room for the next whole word
		while((wordPlace != wl.count) && (filledSack + wordArray[wordPlace].weight <= knapsackSize)) 
		{
//			cout << "in while loop" << endl;
			//write the next word to the file
			for(int i = 0; i<wordArray[wordPlace].weight; i++)
			{
				fprintf(outFile, "%c", wordArray[wordPlace].hufWord[i]);
			}
			fprintf(outFile, "\n");
			
			//update how much 0's 1's the sack has in it
			filledSack = filledSack + wordArray[wordPlace].weight;
			
			//update the value of the sack
			sackValue = sackValue + wordArray[wordPlace].value;
//			cout << "sackValue: " << sackValue << endl;
			
			//move on to next word
			wordPlace++;
		}
		if(wordPlace == wl.count) //we have reached the end of the list
		{//we do nothing
//			cout << "we ran out of words, cant fill the sack more" << endl;
		}
		else if(filledSack + wordArray[wordPlace].weight > knapsackSize)//we have 1 last one to put in, but it is a fraction
		{
//			cout << "filling in a fraction" << endl;
			double spotsLeft = knapsackSize - filledSack;
			for(int i = 0; i<spotsLeft; i++)
			{
				fprintf(outFile, "%c", wordArray[wordPlace].hufWord[i]);
			}
			double percentageOfWord = spotsLeft/wordArray[wordPlace].weight;
//			cout << "PoW: " << percentageOfWord << endl;
			sackValue = sackValue + percentageOfWord*wordArray[wordPlace].value;
//			cout << "sackValue: " << sackValue << endl;
		}
//		cout << "out of writing part" << endl;;
		
		double printableVal = 100*sackValue;
		
		//cout << "100xSackval: " << printableVal << endl;
		printableVal = floor(printableVal + .5);//to deal with rounding
		//cout << "floorded: " << printableVal << endl;
		printableVal = printableVal/100;
		//cout << "back to 2 d's: " << printableVal << endl;
		
		//the COUT answer, the total value in the pack
		cout << printableVal << endl;
		
		
	}
	//0-1 knapsack (dynamic)
	else
	{
		//B == maximum benefit acheived 2d array
		int W = knapsackSizeInt;//ROWS, total capacity
		int n = wl.count;//number of items, colums
		
		int **B =0;
		B = new int *[n+1];
		for(int i = 0; i<n+1; i++)
		{
			B[i] = new int[W+1];
		}
		
		int **included = 0;
		included = new int *[n+1];
		for(int i = 0; i<n+1; i++)
		{
			included[i] = new int[W+1];
		}
		for(int i = 0; i<n+1; i++)
		{
			for(int j =0; j<W+1; j++)
			{
				included[i][j] = 0;
			}
		}
		
		for(int w = 0; w<W+1; w++) //row 0
		{
			B[0][w] = 0;
		}
		for(int k = 1; k<n+1; k++)
		{
			B[k][0] = 0;
			for(int w = 1; w<W+1; w++)
			{
				if(((int)wordArray[k-1].weight <= w) && (B[k-1][w- (int)wordArray[k-1].weight] + wordArray[k-1].value))//weight of the kth element <= w
				{
					B[k][w] = B[k-1][w-(int)wordArray[k-1].weight] + wordArray[k-1].value;
					included[k][w] = 1;
				}
				else
				{
					B[k][w] = B[k-1][w];
				}
			}
		}
//		cout << "Dynamic solution: " << B[n][W] << endl;
		cout << B[n][W] << endl;
		
		int wc = W;
		int nc = n;
		while((wc > 0) && (nc > 0))
		{
			if(included[nc][wc] == 1)//this item was included
			{
				//write the item into the file
				for(int i = 0; i<wordArray[nc-1].weight; i++)
				{
					fprintf(outFile, "%c", wordArray[nc-1].hufWord[i]);
				}
				fprintf(outFile, "\n");
				
				//change wc to wc  - item's weight
				wc = wc - wordArray[nc-1].weight;
			}
			else	//this item is not included
			{
				//go nc--
				nc--;
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		


	}
	
	
	
/*	
	//Which sort,
	if(howSolve == 'f')// if freq, sort by freq highest to lowest
	{
		for(int i =0; i<26; i++)
		{
			for(int j =0; j<i; j++)
			{
				if(alpCount[i] > alpCount[j])
				{
					int alpCountTemp = alpCount[i];
					char alpTemp = alp[i];
					string binSTemp = binaryRepresentation[i];
					
					
					alpCount[i] = alpCount[j];
					alp[i] = alp[j];
					binaryRepresentation[i] = binaryRepresentation[j];
					
					
					alpCount[j] = alpCountTemp;
					alp[j] = alpTemp;
					binaryRepresentation[j] = binSTemp;
				}
			}
		}
	}
		
	//if alph, already sorted
*/	
	
	
/*	
	//printing out letters and count
	cout << "Total Characters: " << totalChars << endl;
	for(int i = 0; i<26; i++)
	{
		//cout << (char)(i+97) << ": " << alpCount[i] << endl;
		cout << alp[i] << ": " << alpCount[i] << " "<< binaryRepresentation[i]<< endl;
	}
*/	
	
	
	fclose(outFile);
	
	return 0;

}


void stringFunc(huffNode * h, char dir, string array[])
{
	if(h->parent == NULL)//root of the graph
	{
		h->sBin = "";
	}
	else//something with a parent (which has its string already since recursive)
	{
		if(dir == 'l')//go left
		{
			h->sBin = h->parent->sBin + "0";
		}
		else if(dir == 'r')//go right
		{
			h->sBin = h->parent->sBin + "1";
		}
	}
	
	if(h->letter != '-')//is a letter
	////put the strings in the binaryRepresentation array
	{
		array[h->letter - 97] = h->sBin;
	}
	
	
	if(h->leftC == NULL && h->rightC == NULL)//no children, done with recursion (they all have 2 or 0 children)
	{
		return;
	}
	else
	{
		stringFunc(h->leftC, 'l', array);
		stringFunc(h->rightC, 'r', array);
	}
	return;
}








