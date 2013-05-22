#include "Player.h"
#include <iostream>

//initialize
Player::Player(){
//	cout << "Hello from Player constructor" << endl;
	FullName = "LOLOLOL LOLOL";
	Position = Guard;
	HeightFt = 4;
	HeightInch = 1;
	Weight = 77;
	Year = JUNIOR;
	Games = 1;
	PPG = 1;
	RPG = 0;
	APG = 1;
	TOPG = 1;
}

//destruct
Player::~Player(){
}

//copy constructor
Player::Player(const Player & other){
	FullName = other.FullName;
	Position = other.Position;
	HeightFt = other.HeightFt;
	HeightInch = other.HeightInch;
	Weight = other.Weight;
	Year = other.Year;
	Games = other.Games;
	PPG = other.PPG;
	RPG = other.RPG;
	APG = other.APG;
	TOPG = other.TOPG;
}

//value constructor
Player::Player(string name, PositionType pos, int hf, int hi, int wt, YearType yr, int g, double p, double r, double a, double to){
	FullName = name;
	Position = pos;
	HeightFt = hf;
	HeightInch = hi;
	Weight = wt;
	Year = yr;
	Games = g;
	PPG = p;
	RPG = r;
	APG = a;
	TOPG = to;
}

bool Player::operator>(Player & second){
	if(PPG > second.PPG){
		return true;
	}
	else{
		return false;
	}
}


//display player mode
void Player::displayPlayerMode(){
	cout <<  endl;
	cout << "PLAYER MENU" << endl;
	cout << "Player: ";
	string name = returnFullName();
	cout << name;
	cout << endl;
	cout << "\tI: Display detailed player information" << endl;
	cout << "\tS: Show this player's scoring average" << endl;
	cout << "\tR: Show this player's rebounding average" << endl;
	cout << "\tH: Show this player's height" << endl;
	cout << "\tQ: Quit and return to the previous menu" << endl;

}

void Player::assignPlayer(string &inname, PositionType inposition, int inheightF, int inheightI, int inweight, YearType inyear, int ingames, double inppg, double inrpg, double inapg, double intopg){
	FullName = inname;
	Position = inposition;
	HeightFt = inheightF;
	HeightInch = inheightI;
	Weight = inweight;
	Year = inyear;
	Games = ingames;
	PPG = inppg;
	RPG = inrpg;
	APG = inapg;
	TOPG = intopg;
}

//
double Player::returnPPG(){
	return PPG;
}

double Player::returnRPG(){
	return RPG;
}

Player * Player::returnPlayer(){
	return this;
}

string Player::returnFullName(){
	return FullName;
}

int Player::returnFullHeight(){
	int fh = 0;
	fh = (HeightFt*12) + HeightInch;
	return fh;
}

void Player::displayStats(){
	cout <<  "\tPosition: ";
	if(Position == Guard){
		cout << "Guard";
	}
	else if(Position == Forward){
		cout << "Forward";
	}
	if(Position == Center){
		cout << "Center";
	}
	cout << "\tHeight: " << HeightFt << "-" << HeightInch;
	cout << "\tWeight: " << Weight << "lbs\tYear: ";
	if (Year == FRESHMAN){
		cout << "Freshman";
	}
	else if(Year == SOPHOMORE){
		cout << "Sophomore";
	}
	else if(Year == JUNIOR){
		cout << "Junior";
	}
	else if(Year == SENIOR){
		cout << "Senior";
	}
	cout << "\tGames Played: " << Games << "\n\t\tPPG: ";
	cout << PPG << "\t\tRPG: " << RPG << "\t\tAPG: " << APG << "\t\tTOPG: " <<TOPG;
	
	return;
}

int Player::returnHeightFt(){
	return HeightFt;
}

int Player::returnHeightInch(){
	return HeightInch;
}
