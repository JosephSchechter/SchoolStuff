#include "Player.h"

using namespace std;

Player::Player(){
}

Player::Player(string s){
	name = s;
	wins = 0;
	losses = 0;
}

void Player::addBottomCard(PlayingCard card){
	deck.push_back(card);
}

PlayingCard Player::removeTopCard(){
	PlayingCard temp;
	temp = deck.front();
	deck.pop_front();
	return temp;
}

string Player::getName(){
	return name;
}

int Player::deckSize(){
	return deck.size();
}

int Player::getNumWins(){
	return wins;
}

int Player::getNumLosses(){
	return losses;
}

void Player::wonGame(){
	wins++;
}

void Player::lostGame(){
	losses++;
}