#include "TownList.h"

using namespace std;

TownList::TownList(){
	head = NULL;
	tail = NULL;
	size = 0;
}

TownList::~TownList(){

	Town * ptr = head;
	Town * temp = NULL;
	while(ptr != NULL){
		temp = ptr->next;
		delete ptr;
		size--;
		ptr=temp;
	}

}

void TownList::insert(string s, int x1, int y1){
	Town * new_town = new Town(s,x1,y1);
	if(head == NULL){	//0 items in list
		head = new_town;
		tail = new_town;
		size++;
	}
	else{	//some items in list
	//adds to the end
		tail->next = new_town;
		new_town->prev = tail;
		tail = new_town;
		size++;
	}
}


int TownList::getSize(){
	return size;
}

