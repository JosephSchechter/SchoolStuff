#include "PlayingCard.h"
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Player{
	public:
		Player();
		Player(string s);
		void addBottomCard(PlayingCard card);
		PlayingCard removeTopCard();
		string getName();
		
		int deckSize();
		int getNumWins();
		int getNumLosses();
		
		void wonGame();
		void lostGame();
	
	private:
		int wins;
		int losses;
		string name;
		int numcards;
		deque<PlayingCard> deck;		
	
};