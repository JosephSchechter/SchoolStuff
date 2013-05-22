#include <iostream>
#include <string>
using namespace std;

class PlayingCard{
	public:
	
/*	
	
	
//		enum CardVal {DEUCE, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
//		enum CardSuit {CLUB, DIAMOND, SPADE, HEART};
//		enum CardSuit {C, D, S, H};
//		PlayingCard(CardSuit cs, CardVal cv);
//		PlayingCard(CardSuit cs, int cv);
*/

		
		PlayingCard();
		PlayingCard(char cs, int cv);
		
		int getCardVal();
		char getCardSuit();
		
		
		string displayCard();

		bool operator==(PlayingCard& other);
		bool operator>(PlayingCard& other);
		bool operator<(PlayingCard& other);

		~PlayingCard();
		
	private:
//		CardVal value;
		int value;
//		CardSuit suit;
		char suit;


};
