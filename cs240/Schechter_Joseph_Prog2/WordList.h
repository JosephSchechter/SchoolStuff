#include "WordListNode.h"
#include <string>

using namespace std;

class WordList{
	public:
		WordList();
		~WordList();

		void insert(string s);
		int getSize();

		WordListNode * head;
		WordListNode * tail;


	private:
		int size;


};
