#include "PlayingCard.h"

PlayingCard::PlayingCard(){
	//doesnt do anything
}

PlayingCard::PlayingCard(char cs, int cv){
	value = cv;
	suit = cs;
}
		
int PlayingCard::getCardVal(){
	return value;
}

char PlayingCard::getCardSuit(){
	return suit;
}

PlayingCard::~PlayingCard(){
}


string PlayingCard::displayCard(){
	string out = "";
	
	//Value
	switch(value){
		case 2:
			out = "2";
			break;
		case 3:
			out = "3";
			break;
		case 4:
			out = "4";
			break;
		case 5:
			out = "5";
			break;
		case 6:
			out = "6";
			break;
		case 7:
			out = "7";
			break;
		case 8:
			out = "8";
			break;
		case 9:
			out = "9";
			break;
		case 10:
			out = "10";
			break;
		case 11:
			out = "J";
			break;
		case 12:
			out = "Q";
			break;
		case 13:
			out = "K";
			break;
		case 14:
			out = "A";
			break;
	}
	
	//Suit
	switch(suit){
		case 'C':
			out = out + "C";
			break;
		case 'D':
			out = out + "D";
			break;
		case 'S':
			out = out + "S";
			break;
		case 'H':
			out = out + "H";
			break;
	}
	return out;
}


bool PlayingCard::operator==(PlayingCard& other){
	if(value == other.value){
		return true;
	}

	else {
		return false;
	}
}

bool PlayingCard::operator>(PlayingCard& other){
	if(value > other.value){
		return true;
	}

	else {
		return false;
	}
}


bool PlayingCard::operator<(PlayingCard& other){
	if(value < other.value){
		return true;
	}

	else {
		return false;
	}
}
