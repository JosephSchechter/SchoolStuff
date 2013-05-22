#include "WordListNode.h"
#include <string>

using namespace std;

WordListNode::WordListNode(string data_input){
	data = data_input;
	next = NULL;
	prev = NULL;
	
}

WordListNode::WordListNode(){
//never called
	data = "AAAAAAAAA";
	next = NULL;
	prev = NULL;
}

WordListNode::~WordListNode(){
//done
}



