#include "WordList.h"

using namespace std;


WordList::WordList(){
	head = NULL;
	tail = NULL;
	size = 0;
}


WordList::~WordList(){
	WordListNode * ptr = tail;
	WordListNode * temp = NULL;
	//GO FROM BOTTOM UP
	while(ptr != NULL){
		temp = ptr->prev; //could be null
		delete ptr;
		size--;
		ptr = temp;
	}
}

void WordList::insert(string s){
	WordListNode * new_node = new WordListNode(s);
	if(head == NULL){ //0 items
		head = new_node;
		tail = new_node;
		size++;
	}
	else { //there is something in the list
		tail->next = new_node;
		new_node->prev = head;
		tail = new_node;
		size++;
	}
}

int WordList::getSize(){
	return size;
}
