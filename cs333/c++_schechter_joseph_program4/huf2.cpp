#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALP 26

using namespace std;

//node
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

//linked list
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


void stringFunc(huffNode * h, char dir, string array[]);


int main(int argc, char* argv[])
{

	if(argc != 2)
	{
		cout << "correct usage: ./huffman -{af}" << " exiting" << endl;
		return 0;
	}
	
	char howSort = 'x'; //a or f
	
	if(strlen(argv[1]) != 2)	//length of 2
	{
		cout << "have it be either \"-a\" or \"-f\", nothing else, exiting" << endl;
		return 0;
	}
	if(argv[1][0] != '-')		//starts with -
	{
		cout << "have it be either \"-a\" or \"-f\", nothing else, exiting" << endl;
		return 0;
	}
	
	
	if(argv[1][1] == 'a')		//a
	{
//		cout << "Sorted alphabetically" << endl;
		howSort = 'a';
	}
	else if(argv[1][1] == 'f')	//f
	{
//		cout << "Sorted by Frequency" << endl;
		howSort = 'f';
	}
	else
	{
		cout << "have it be either \"-a\" or \"-f\", nothing else, exiting" << endl;
		return 0;
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
	char c = 'a';
	while((c = getchar()) != EOF)
	{
		if (c == '\n') //do nothing
		{
			//cout << "NEWLINE" << endl;
		}
		else	//finds a letter a-z
		{
			if((c >= 97) && (c <= 122))
			{
			//cout << c << endl;
				alpCount[(c-97)]++;
				totalChars++;
			}
			else
			{
				cout << "\nweird character in input file, exiting";
				return 0;
			}
		}
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

	
	//printing out letters and count
	cout << "Total Characters: " << totalChars << endl;
	for(int i = 0; i<26; i++)
	{
		//cout << (char)(i+97) << ": " << alpCount[i] << endl;
		cout << alp[i] << ": " << alpCount[i] << endl;
	}

	
	
	
	//put them into the linked list
	huffList hl;
	hl.count = 0;
	hl.head = NULL;	
	for(int i = 0; i <26; i++)
	{
		hl.insert(alp[i], alpCount[i]);
	}
	
	
	//check
	cout << "\ncheck\n";
	huffNode *tempNode = hl.head;
	for(int i =0; i<26; i++)
	{
		cout << tempNode->letter << ": " << tempNode->freq << endl;
		tempNode = tempNode->next;
		
	}


	
	//build the huffman tree in the ll
	huffNode *new_node;
	huffNode *position;
//	cout <<"\ntest1\n";
	while(hl.count > 1)
	{
	
		//check2
		cout << "\ncheck2\n";
		tempNode = hl.head;
		for(int i =0; i<hl.count; i++)
		{
			cout << tempNode->letter << ": " << tempNode->freq << endl;
			tempNode = tempNode->next;
			
		}
		
	
	
		cout <<"\ntest2\n";
		
		//Create new node
		new_node = new huffNode;
		new_node->letter = '-';//not a real letter
		new_node->prev = NULL;
		new_node->next = NULL;
		
		cout <<"\ntest2.1\n";
		
		//Remove first node and make it left subtree
		new_node->leftC = hl.head;
		hl.head->parent = new_node;
		hl.head = hl.head->next;
		
		cout <<"\ntest2.2\n";
		
		//Remove second node and make it right subtree
		new_node->rightC = hl.head;
		cout <<"\ntest2.2.1\n";
		
		hl.head->parent = new_node;
		cout <<"\ntest2.2.2\n";
		hl.head = hl.head->next;
		
		cout <<"\ntest3\n";
		//Frequency of new node equals sum of frequency of left and right children
		new_node->freq = new_node->rightC->freq + new_node->leftC->freq;
		
		
		cout <<"\ntest4\n";
		
		//Place new node back into list into sorted position
		if(hl.head == NULL)//there were only 2 items in the list, now there are 0, put that 1 parent in
		{
			hl.head = new_node;
		}
		else//there is at least 1 item to search through to see where the new node needs to be put
		{
			position = hl.head;
			cout <<"\ntest5\n";
			
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
					else
					{
						new_node->prev->next = new_node;
					}
					
					position = NULL;
				}
				else //new node is bigger or equal to current node position is looking at
				{
					if(position->next == NULL)//if its the last in the list, put the new node at the end of list
					{
						position->next = new_node;
						new_node->prev = position;
						position = NULL;
					}
					else
					{
						position = position->next;
					}
				}
			}
		}
		
		
		
		cout <<"\nloop\n";
		hl.count--;
		cout << "hl count: " << hl.count<<endl;
		new_node = NULL;
	
	}
	
	
	
	cout << "out";

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

	
	
	
	
	
	//Which sort,
	if(howSort == 'f')// if freq, sort by freq highest to lowest
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
	
	
	
	
	//printing out letters and count
	cout << "Total Characters: " << totalChars << endl;
	for(int i = 0; i<26; i++)
	{
		//cout << (char)(i+97) << ": " << alpCount[i] << endl;
		cout << alp[i] << ": " << alpCount[i] << "\t"<< binaryRepresentation[i]<< endl;
	}
	
	
	
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








