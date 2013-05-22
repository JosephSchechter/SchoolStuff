#include <string>

using namespace std;

class Town{
	public:
		Town(string namein, int xin, int yin);
		Town();
		~Town();


		//data members
		//name of the town
		string name;
		//x coordinate
		int x;
		//y coordinate
		int y;


		//pointers to other towns in the list
		Town * prev;
		Town * next;

};
