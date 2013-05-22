#include "Game.h"


Game::Game(){
//do nothing
}

//Game::Game(Player & player1, Player & player2, string outie){
Game::Game(Player * player1, Player * player2, string outie){
	p1 = player1;
	p2 = player2;
	outputName = outie;
	
	numbattles = 0;
	numwars = 0;
	
	dealCards();
	
//	Player * winner;
//	Player * other;
	winner = NULL;
	other = NULL;
	
	winner = play();
	if(winner==p1){
		other = p2;
	}
	else{
		other = p1;
	}
	//Jane (1) DEFEATED John in 120 Battles and 13 Wars
/*	
	cout << p1->getName() << " (" << p1->getNumWins() << ") DEFEATED " << p2->getName() << " in " << numbattles << " Battles and " << numwars << " Wars.";
	cout << endl;
*/	
	output.open(outputName.data(), ios::app);
	output << winner->getName() << " (" << winner->getNumWins() << ") DEFEATED " << other->getName() << " in " << numbattles << " Battles and " << numwars << " Wars.";
	output << endl;
	output.close();
	
//	cout << "END RESULTS: " << p1->getName() << " " << p1->deckSize() << ", " << p2->getName() << " " << p2->deckSize() << endl;
}


Game::~Game(){
}
	

	
Player * Game::play(){


	//open up the ofstream
	output.open(outputName.data(), ios::app);//starts writing at end of last write
//	output << endl;
	output << "===" << endl;
	output << p1->getName() << " VS. " << p2->getName() << endl;
	output.close();

/*
	cout << endl;
	cout << "===" << endl;
	cout << p1->getName() << " VS. " << p2->getName() << endl;
*/
	
	
	p1Lowest = 26;
	p2Lowest = 26;
	while( (p1->deckSize() != 0) && (p2->deckSize() != 0) ) //keep battling until someone has 0 cards
	{
		if(p1Lowest > p1->deckSize()){
			p1Lowest = p1->deckSize();
		}
		if(p2Lowest > p2->deckSize()){
			p2Lowest = p2->deckSize();
		}

		battle();
	}
	
	
	
	if(p1->deckSize() == 0){ //p1 lost , p2 won
		comeback = p2Lowest;
		p1->lostGame();
		p2->wonGame();
		
		for(int f=0; f<52; f++){
			p2->removeTopCard();
		}		
		
		return p2;
	}
	else{ //p1 won
		comeback = p1Lowest;
		p2->lostGame();
		p1->wonGame();
		for(int f=0; f<52; f++){
			p1->removeTopCard();
		}		
		return p1;
	}
	
	
	
	if(output.is_open()){
		output.close();
	}
	
}

void Game::battle(){
	numbattles++;
	
	PlayingCard card1; //p1's play
	PlayingCard card2; //p2's play
	//at first, we know both players have some number of cards.
	card1 = p1->removeTopCard();
	card2 = p2->removeTopCard();
	
	startDeck.push_back(card1);
	startDeck.push_back(card2);
	
	random_shuffle(startDeck.begin(), startDeck.end());
	
	PlayingCard tmp;
	
	output.open(outputName.data(), ios::app);
	output << "\t Battle " << numbattles << ": ";
	output.close();

/*	
	cout << "\t Battle " << numbattles << ": ";
*/
	
	int pilesize = startDeck.size();
	
	if(card1 > card2){
		for(int i = 0; i < pilesize; i++){
			tmp = startDeck.front();
			startDeck.pop_front();
			p1->addBottomCard(tmp);
		}
		output.open(outputName.data(), ios::app);
		output << p1->getName() << " (" << card1.displayCard() << ")" <<" defeated " << p2->getName() << " (" << card2.displayCard() << ")";
		output << ": " << p1->getName() << " " << p1->deckSize() << ", " << p2->getName() << " " << p2->deckSize() << endl;
		output.close();
/*
		cout << p1->getName() << "(" << card1.displayCard() << ")" <<" DEFEATED " << p2->getName() << "(" << card2.displayCard() << ")";
		cout << ": " << p1->getName() << " " << p1->deckSize() << ", " << p2->getName() << " " << p2->deckSize() << endl; 
*/
	}
	
	else if(card1 < card2){
		for(int i = 0; i < pilesize; i++){
			tmp = startDeck.front();
			startDeck.pop_front();
			p2->addBottomCard(tmp);
		}
		output.open(outputName.data(), ios::app);
		output << p2->getName() << " (" << card2.displayCard() << ")" <<" defeated " << p1->getName() << " (" << card1.displayCard() << ")";
		output << ": " << p1->getName() << " " << p1->deckSize() << ", " << p2->getName() << " " << p2->deckSize() << endl;
		output.close();
/*		
		cout << p2->getName() << "(" << card2.displayCard() << ")" <<" DEFEATED " << p1->getName() << "(" << card1.displayCard() << ")";
		cout << ": " << p1->getName() << " " << p1->deckSize() << ", " << p2->getName() << " " << p2->deckSize() << endl;
*/
	}
	
	else if(card1 == card2){
		output.open(outputName.data(), ios::app);
		output << p1->getName() << " (" << card1.displayCard() << ")" <<" tied " << p2->getName() << " (" << card2.displayCard() << ")";
		output << endl;
		output.close();
/*	
		cout << p1->getName() << "(" << card1.displayCard() << ")" <<" tied " << p2->getName() << "(" << card2.displayCard() << ")";
		cout << endl;
*/
		war();
	}	
}

void Game::war(){
	numwars++;
	
	output.open(outputName.data(), ios::app);
	output << "\t War " << numwars << ": ";
	output.close();
	
/*	
	cout << "\t War " << numwars << ": ";
*/	
	
	int pilesize = startDeck.size(); 
	
	if(p1->deckSize() < 4){ //player 1 cant play war, so they lose, p2 wins game
		PlayingCard tmp;
		int p1pilesize = p1->deckSize();
		for(int i = 0; i < p1pilesize; i++){
			tmp = p1->removeTopCard();
			p2->addBottomCard(tmp);
		}
		for(int i = 0; i < pilesize; i++){
			tmp = startDeck.front();
			startDeck.pop_front();
			p2->addBottomCard(tmp);
		}
		
		output.open(outputName.data(), ios::app);
		output << p2->getName() << " defeated " << p1->getName() << " in war since " << p1->getName() << " ran out of cards mid-war!";
		output << endl;
		output.close();
/*		
		cout << p2->getName() << " DEFEATED " << p1->getName() << " in war since " << p1->getName() << " ran out of cards mid-war!";
		cout << endl;
*/
	}
	else if(p2->deckSize() < 4){ //player 2 cant play war, so they lose, p1 wins game
		PlayingCard tmp;
		int p2pilesize = p2->deckSize();
		for(int i = 0; i < p2pilesize; i++){
			tmp = p2->removeTopCard();
			p1->addBottomCard(tmp);
		}
		for(int i = 0; i < pilesize; i++){
			tmp = startDeck.front();
			startDeck.pop_front();
			p1->addBottomCard(tmp);
		}
		output.open(outputName.data(), ios::app);
		output << p1->getName() << " defeated " << p2->getName() << " in war since " << p2->getName() << " ran out of cards mid-war!";
		output << endl;
		output.close();
/*		
		cout << p1->getName() << " DEFEATED " << p2->getName() << " in war since " << p2->getName() << " ran out of cards mid-war!";
		cout << endl;
*/		
	}
	
	else //everyone has enough cards to play
	{
		PlayingCard tmp;
		//get 3 down cards from p1 and put them in startDeck
		for(int z = 0; z < 3; z++){
			tmp = p1->removeTopCard();
			startDeck.push_front(tmp);
		}
		//get 3 down cards from p2 and put them in startDeck
		for(int y = 0; y < 3; y++){
			tmp = p2->removeTopCard();
			startDeck.push_front(tmp);
		}
		//now theres 6 cards in there, and we call battle we look at 7 and 8
		warBattle(); 	//slightly different than battle, doesnt print out a bunch of things, and doesnt increment battles
	}	
}



void Game::warBattle(){	
	PlayingCard card1; //p1's play
	PlayingCard card2; //p2's play
	//at first, we know both players have some number of cards, checked from other functions
	card1 = p1->removeTopCard();
	card2 = p2->removeTopCard();
	
	startDeck.push_back(card1);
	startDeck.push_back(card2);
	
	random_shuffle(startDeck.begin(), startDeck.end());
	
	PlayingCard tmp;
	
	int pilesize = startDeck.size();
	
	if(card1 > card2){
		for(int i = 0; i < pilesize; i++){
			tmp = startDeck.front();
			startDeck.pop_front();
			p1->addBottomCard(tmp);
		}
		output.open(outputName.data(), ios::app);
		output << p1->getName() << " (" << card1.displayCard() << ")" <<" defeated " << p2->getName() << " (" << card2.displayCard() << ")";
		output << ": " << p1->getName() << " " << p1->deckSize() << ", " << p2->getName() << " " << p2->deckSize() << endl;
		output.close();
		
/*		
		cout << p1->getName() << "(" << card1.displayCard() << ")" <<" DEFEATED " << p2->getName() << "(" << card2.displayCard() << ")";
		cout << ": " << p1->getName() << " " << p1->deckSize() << ", " << p2->getName() << " " << p2->deckSize() << endl;
*/
	}
	
	else if(card1 < card2){
		for(int i = 0; i < pilesize; i++){
			tmp = startDeck.front();
			startDeck.pop_front();
			p2->addBottomCard(tmp);
		}
		output.open(outputName.data(), ios::app);
		output << p2->getName() << " (" << card2.displayCard() << ")" <<" defeated " << p1->getName() << " (" << card1.displayCard() << ")";
		output << ": " << p1->getName() << " " << p1->deckSize() << ", " << p2->getName() << " " << p2->deckSize() << endl;
		output.close();
/*		
		cout << p2->getName() << "(" << card2.displayCard() << ")" <<" DEFEATED " << p1->getName() << "(" << card1.displayCard() << ")";
		cout << ": " << p1->getName() << " " << p1->deckSize() << ", " << p2->getName() << " " << p2->deckSize() << endl;
*/		
	}
	
	else if(card1 == card2){
		output.open(outputName.data(), ios::app);
		output << p1->getName() << " (" << card1.displayCard() << ")" <<" tied " << p2->getName() << " (" << card2.displayCard() << ")";
		output << endl;
		output.close();
		
/*		
		cout << p1->getName() << "(" << card1.displayCard() << ")" <<" tied " << p2->getName() << "(" << card2.displayCard() << ")";
		cout << endl;
*/		
		war();
	}	
}



		
void Game::dealCards(){
	//makes a deck of all cards
	for(int i = 2; i <=14 ; i++){ //value
		for(int j = 0; j < 4; j++){ //suit
			switch(j){
				case 0:
					startDeck.push_front(PlayingCard('C', i)); //PlayingCard(suit, value)
					break;
				case 1:
					startDeck.push_front(PlayingCard('D', i)); //PlayingCard(suit, value)
					break;
				case 2:
					startDeck.push_front(PlayingCard('S', i)); //PlayingCard(suit, value)
					break;
				case 3:
					startDeck.push_front(PlayingCard('H', i)); //PlayingCard(suit, value)
					break;
			}
		}
	}
	
	//deal the cards to the players
	random_shuffle(startDeck.begin(), startDeck.end());
	PlayingCard temp(0,0);
	for(int p = 0; p < 52; p++){
		temp = startDeck.front();
		startDeck.pop_front();
		if(p%2 == 0){
			p1->addBottomCard(temp);
		}
		else {
			p2->addBottomCard(temp);
		}
	}
}
		
int Game::getBattles(){
	return numbattles;
}	

int Game::getComeback(){
	return comeback;
}

Game& Game::operator=(const Game &other) {
// Do the assignment operation!
	outputName = other.outputName;
	p1=other.p1;
	p2=other.p2;
	startDeck=other.startDeck;
	numbattles = other.numbattles;
	numwars = numwars;
	p1Lowest = other.p1Lowest;
	p2Lowest = other.p2Lowest;
	comeback = other.comeback;

    return *this;  // Return a reference to myself.
}
/*
string Game::getWinnerName(){
	return winner->getName();
}


string Game::getLoserName(){
	return other->getName();
}
*/
