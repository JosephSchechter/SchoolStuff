#include <string>
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include "Game.h"
#include "WordList.h"


using namespace std;

Player * tournament(vector<Player*> vec);

string infile = "";	//input file name
string outfile = "";	//output file name
int gameCounter = 0;
Game * gameArray = NULL;

int main(int argc, char *argv[]){

	srand(time(NULL));

//	string infile = "";	//input file name
//	string outfile = "";	//output file name
//	cout << "number of args: " << argc;

	switch(argc){
		case 3:
			infile = argv[1];
			outfile = argv[2];
			break;
		default:
			cout << "\n Not enough elements in your war call. EXITING" << endl;
			return 0;
	}
	


	ifstream in;
	in.open(infile.data());
	if(in.fail()){
		cout << "\nBad input file name. EXITING" << endl;
		return 0;
	}
	
	//Make a linked list of names to get a count and makes it easier to make a bunch of players later
	string word = "";
	WordList pNames;
	while(!in.eof())
	{
		getline(in, word); //gets the name from in and puts it in word
		if(word != ""){
			///PUT THE DATA INTO A LIST TO GET A COUNT O(n)
			pNames.insert(word);			
			word = "";
		}
	}
	in.close();//dont need to input anymore!
	
	int numPlayers = pNames.getSize();
	cout << "number of players: " << numPlayers << endl;
	

	if(numPlayers <= 1){
		if (numPlayers == 1){
			cout << "With 1 player, there are no games, so...";
		}
		cout << "EXITING" << endl;
		return 0;
	}

	
	//algorithm to check if x is a power of 2: (x & (x-1)) == 0, logical AND
	if( (numPlayers & (numPlayers-1)) != 0 )
	{
		cout << "\nBad number of players. EXITING." << endl;
		return 0;
	}
	else 
	{
		cout << "\n LET'S PLAY \n";
	}
	
	//make an array of games
	gameArray = new Game[numPlayers-1]; //if theres 8 players, theres gunna be 7 games
	
	//make an array of all the players
	Player * PlayerArray = NULL;
	PlayerArray = new Player[numPlayers];
	WordListNode * wln = pNames.head;
	for(int p = 0; p < numPlayers; p++){
		PlayerArray[p] = Player(wln->data);
		wln=wln->next;
	}
	
	//make a vector of all pointers to players
	vector<Player*> myvec;
	for(int d = 0; d<numPlayers; d++){
		myvec.push_back(&(PlayerArray[d]));
	}
	
	//resets out.txt
	ofstream oott;
	oott.open(outfile.data());
	oott.close();
	
	
	
	Player * winnar;
	winnar = tournament(myvec);

//    * The winner of the tournament
	cout << endl;
	cout << "The Winner of the tournament: " << winnar->getName() << endl;

	
	//numplayers-1 is the number of games, fyi
	
	
	
//    * The average number of battles per matchup
	double avgNumBattles = 0; 
	for(int q=0; q<(numPlayers-1); q++){
		avgNumBattles = avgNumBattles + gameArray[q].getBattles();
	}
	avgNumBattles = avgNumBattles/(numPlayers-1);
	cout<<"The average number of battles per matchup is: " << avgNumBattles << endl;
	
//    * The largest number of battles in any one matchup
	int largestNumBattles = 0;
	for(int q=0; q<(numPlayers-1); q++){
		if(largestNumBattles < gameArray[q].getBattles()){
			largestNumBattles = gameArray[q].getBattles();
		}
	}
	cout << "The largest number of battles in a single game: " << largestNumBattles << endl;

//    * The biggest comeback (i.e. the fewest number of cards that a player had before coming back to win her matchup)
	int biggestComeback = gameArray[0].getComeback();
	int spot = 0;
	for(int c = 1; c<(numPlayers-1); c++){
		if(biggestComeback > gameArray[c].getComeback()){
			biggestComeback = gameArray[c].getComeback();
			spot = c;
		}
	}
	cout << "The biggest comeback of the tournament was from " << biggestComeback << " card(s)";
	cout << endl;
	
	cout << "END PROGRAM!";
	cout << endl;
	
	delete [] gameArray;
	delete [] PlayerArray;
	
	
	return 0;
}


Player * tournament(vector<Player*> vec){
	if(vec.size() == 1){
		return vec[0]; //returns a pointer to the winner
	}
	for(int i = 0; i<vec.size(); i=i+2){ //hold a game bewteen every pair next to eachother
		gameArray[gameCounter] = Game(vec[i], vec[i+1], outfile);
		gameCounter++;
	}
//	int startvecsize = vec.size();
	for(int j = 0; j<vec.size(); j++){ //kick out the losers
		if(vec[j]->getNumLosses()  > 0){
				//example online
				// erase the 6th element
				// myvector.erase (myvector.begin()+5);
			vec.erase(vec.begin()+j);
			j--;
		}
	}
	
	return tournament(vec);
}




