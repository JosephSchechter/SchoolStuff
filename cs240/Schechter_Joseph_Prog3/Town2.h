#include <string>

using namespace std;

class Town2{
	public:
		Town2(string namein, int xin, int yin);
		Town2();
		~Town2();

		string getName();
		
		int getX();
		int getY();
		int getDist();
		int getPrev();

		int neighborPos[4];//0 is north, 1 is south, 2 is east, 3 is west
		//data members
		//name of the town
		string name;
		//x coordinate
		int x;
		//y coordinate
		int y;
		//distance from where you want to go, originally, it starts at "infinity"
		int dist;
		//the previous node it came from, it will be -1 beginning
		int prev;
};
