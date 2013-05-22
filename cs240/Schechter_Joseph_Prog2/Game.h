#include "Player.h"
#include <iostream>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <fstream>



using namespace std;

class Game{
	public:
		Game();
//		Game(Player & player1, Player & player2, string outie);
		Game(Player * player1, Player * player2, string outie);
		~Game();
		
		Player * play();
		void battle();
		void war();
		void warBattle();
		
		void dealCards();
		
		int getBattles();
		
		int getComeback();
	
		Game& operator=(const Game &other);
/*		
		string getWinnerName();
		string getLoserName();
*/		
	private:
		ofstream output;
		string outputName;
		
		Player * p1;
		Player * p2;
		deque<PlayingCard> startDeck;
		
		int numbattles;
		int numwars;
		
		int p1Lowest; //lowest amount of cards that they had in hand ever in game
		int p2Lowest; //lowest amount of cards that they had in hand ever in game
		int comeback; //lowest amount of cards that the WINNER had in hand ever in came

		Player * winner;
		Player * other;
};