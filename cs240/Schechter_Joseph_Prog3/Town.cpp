#include "Town.h"

using namespace std;

Town::Town(string namein, int xin, int yin){
	name = namein;
	x = xin;
	y = yin;
	next = NULL;
	prev = NULL;
}

Town::Town(){
//Never happening
}


Town::~Town(){
//done
}
