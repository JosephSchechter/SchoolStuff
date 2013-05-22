#include <string>

using namespace std;


class WordListNode {
	public:

		// Create a linked list node by setting its data to the input parameter
		// and the next node in the linked list to NULL (0)
		WordListNode(string data_input);

		//The default constructor doesn't initialize the data members
		WordListNode();

		~WordListNode();

		// Contains the data of the linked list node
		string data;	

		// Contains a pointer to the next item in the linked list
		WordListNode * next;
   
		// Contains a pointer to the previous item in the linked list
		WordListNode * prev;
};
