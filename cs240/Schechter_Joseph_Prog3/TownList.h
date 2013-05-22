#include "Town.h"

using namespace std;

class TownList{
	public:
		TownList();
		~TownList();

		void insert(string s, int x1, int y1);
		int getSize();
		
		Town * head;
		Town * tail;
	
	private:
		int size;
};
