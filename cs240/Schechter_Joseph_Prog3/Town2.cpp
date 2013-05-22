#include "Town2.h"

using namespace std;

Town2::Town2(string namein, int xin, int yin){
	name = namein;
	x = xin;
	y = yin;

	for(int i=0; i<4; i++){
		neighborPos[i] = -1;
	}
	dist = 9999999;
	prev = -1;
}

Town2::Town2(){
//Never happening
	name = "AANANANANAOAONA";
	x= 99999999;
	y= 99999999;
	dist = 9999999;
	prev = -1;
	for(int i=0; i<4; i++){
		neighborPos[i] = -1;
	}
}


Town2::~Town2(){
//done
}

string Town2::getName(){
	return name;
}

int Town2::getX(){
	return x;
}

int Town2::getY(){
	return y;
}

int Town2::getDist(){
	return dist;
}

int Town2::getPrev(){
	return prev;
}