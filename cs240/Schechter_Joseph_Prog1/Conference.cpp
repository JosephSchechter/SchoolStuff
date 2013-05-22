#include "Conference.h"
#include <iostream>
#include <fstream>
#include <string>
#define NUMTEAMS 9

//initialize
Conference::Conference(){
//	cout << "Hello from Conference constructor" << endl;
}


//destruct
Conference::~Conference(){
}


//copy constructor
Conference::Conference(const Conference & other){
	for(int i = 0; i < NUMTEAMS; i++){
		TeamArray[i] = other.TeamArray[i];
	}
}

//


//display conference mode
void Conference::displayConfMode(){
	cout <<  endl;
	cout << "CONFERENCE MENU" << endl;
	//Conference Mode should show the user the following options and "command prompt":
	cout << "Conference: " << endl;
	cout << "\tt: List teams - Names only" << endl;
	cout << "\tT: List teams - Detailed view" << endl;
	cout << "\ts: Show the name of the highest scoring player in the conference" << endl;
	cout << "\tS: Show the name of the highest scoring player in the conference, and switch to enter queries about that player" << endl;
	cout << "\th: Show the name of the tallest player in the conference" << endl;
	cout << "\tH: Show the name of the tallest player in the conference and switch to enter queries about that player" << endl;
	cout << "\tD: Drill down to select and enter queries about a particular team" << endl;
	cout << "\tF: Enter queries about the first place team" << endl;
	cout << "\tQ: Quit this program " << endl;
}

//team selection mode
void Conference::displayTeamSelectMode(){
	int i = 1;
	int j = NUMTEAMS;
	cout << endl;
	cout << "TEAM SELECT MENU" << endl;
	cout << "Select a Team: " << endl;
	while(i<=j)
	{
		cout << "\t"<< i << ". ";
		TeamArray[i-1].teamListTeamSimple();
		cout <<  endl;
		i++;
	}
	cout << "\t0: Quit and return to the previous menu " << endl;
}

//This reads in an istream of what is in a text file that contains 9 .txt locations
//It then does an istream for each of the 9 teams and >>'s into those 9 teams in 
//the array
istream& operator>>(istream& in, Conference& conf){
//	cout << "\nREADING THE conference.txt"<<endl;
//	conf.privatedata = 1;
	int counter = 0;
	string teamTextFileName = "";
	while((!in.eof()) && (counter < NUMTEAMS))
	{
		getline(in, teamTextFileName);
		ifstream teamTextFile;
		teamTextFile.open(teamTextFileName.data());
		teamTextFile >> conf.TeamArray[counter];
		counter++;
	}
	return in;
}

Team * Conference::getTeam(int number){
	Team * tempTeam = &(TeamArray[number-1]);
	return tempTeam;
}


void Conference::confListTeamsSimple(){
	for(int i = 0; i < NUMTEAMS;  i++){
		cout << "\t";
		cout << i+1 << ": ";
		TeamArray[i].teamListTeamSimple();
		cout<<endl;
	}
}

void Conference::confListTeamsComplex(){
	for(int i = 0; i < NUMTEAMS;  i++){
		cout << "\t";
		cout << i+1 << ": ";
		TeamArray[i].teamListTeamComplex();
		cout<<endl;
	}
}

Team * Conference::confGetFirstPlaceTeam(){
	Team * t2 = NULL;
	Team * first = &(TeamArray[0]); //start best team as 1st one [0]
	for(int i = 1; i < NUMTEAMS; i++)
	{
		t2 = &(TeamArray[i]);
		if (t2->betterThanTeam(first))
		{
			first = t2;
		}
	}
	first->teamListTeamSimple();
	cout << " is the First Place Team";
	cout << endl;
	return first;
}

void Conference::confDisplayHighScorePlayer(){
	//cout << "\nconfDisplayHighScorePlayer()\n";
	Player * out = confGetHighScorePlayer();
	string str = out->returnFullName();
	cout << "\n" << str << endl;
}


Player * Conference::confGetHighScorePlayer(){
	Player * BestPlayersOfTeams[NUMTEAMS];
	//cout << "confGetHighScorePlayer()" << endl;
	int i=0;
	//assigns pointers of the best player of each team to an array of player ptrs
	for(i=0; i<NUMTEAMS; i++){
		BestPlayersOfTeams[i] = TeamArray[i].teamGetHighScorePlayer();
		//cout << BestPlayersOfTeams[i]->returnFullName() << endl;
	}
	//cout << "\n_______\n";
	Player * HighScorePlayerOfAll = BestPlayersOfTeams[0];
	//gets the points of the players, compares them, if the player better than best, replaces the pointer
	for(i=1 ; i<NUMTEAMS; i++){
		if(BestPlayersOfTeams[i]->returnPPG() > HighScorePlayerOfAll->returnPPG())
		{
			HighScorePlayerOfAll = BestPlayersOfTeams[i];
		}
	}
	return HighScorePlayerOfAll;
}


void Conference::confDisplayTallestPlayer(){
	//cout << "\nconfDisplayTallestPlayer()\n";
	Player * out = confGetTallestPlayer();
	string str = out->returnFullName();
	cout << "\n" << str << endl;
}


Player * Conference::confGetTallestPlayer(){
	Player * TallestPlayersOfTeams[NUMTEAMS];
	int i=0;
	//cout << "\nconfGetTallestPlayer()\n";
	//assigns pointers of the tallest player of each team to an array of player ptrs
	for(i=0; i<NUMTEAMS; i++){
		TallestPlayersOfTeams[i] = TeamArray[i].teamGetTallestPlayerOfTeam();
		//cout << TallestPlayersOfTeams[i]->returnFullName() << endl;
	}
	Player * TallestOfAll = TallestPlayersOfTeams[0];
	//gets the points of the players, compares them, if the player taller than tallest, replaces the pointer
	for(i=1 ; i<NUMTEAMS; i++){
		if(TallestPlayersOfTeams[i]->returnFullHeight() > TallestOfAll->returnFullHeight()){
			TallestOfAll = TallestPlayersOfTeams[i];
		}
	}
	return TallestOfAll;
}

