#include "Team.h"
#include <iostream>

//initialize
Team::Team(){
//	cout << "Hello from Team constructor" << endl;
}

//destruct
Team::~Team(){
//delete all the players
	delete [] PlayerArrayPtr;
//the rest will go away on its own
}

//display team mode
void Team::displayTeamMode(){
	cout << endl;
	cout << "TEAM MENU" << endl;
	cout << "Team: ";
	teamListTeamSimple();
	//SHOW TEAM NAME   UMBC Retrievers
	cout <<  endl;
	cout << "\tI: Display detailed team information"<<endl;
	cout << "\tp: List players - Names only"<<endl;
	cout << "\tP: List players - Detailed view"<<endl;
	cout << "\tD: Drill down to display information about a particular player"<<endl;
	cout << "\tS: Show the name of the highest scoring player on the team"<<endl;
	cout << "\tH: Show the name of the tallest player on the team"<<endl;
	cout << "\tQ: Quit and return to the previous menu "<<endl;
}

//player selection mode
void Team::displayPlayerSelectMode(){
	//display all players on current team numbered 1 to N
	cout <<  "PLAYER SELECT MENU" << endl;
	cout << "Select a Player: " << endl;
	teamListPlayersSimple();	
	cout << "\t0: Quit and return to the previous menu" << endl; 
}

bool Team::operator>(Team & second){
	if(confWins > second.confWins){
		return true;
	}
	else{
		return false;
	}
}


istream& operator>>(istream & in, Team & t){
	string inSchool;
	string inMascot;
	int inConfWins, inConfLoss, inOverallWins, inOverallLoss;
	int inNumPlayers=1;
	
	getline(in, inSchool);
	t.School = inSchool;
	getline(in, inMascot);
	t.Mascot = inMascot;
	
	in >> inConfWins >> inConfLoss >> inOverallWins >> inOverallLoss;
	t.confWins = inConfWins;
	t.confLoss = inConfLoss;
	t.overallWins = inOverallWins;
	t.overallLoss = inOverallLoss;
//	cout << t.School << " conf wins : " << t.confWins<<endl;
	
	in >> inNumPlayers;
	t.numberPlayers = inNumPlayers;
	t.PlayerArrayPtr = new Player[t.numberPlayers];
	
	string inFirstName;
	string inLastName;
	Player::PositionType inPosition;
	int inHeightFt;
	char dash;
	char letter;
	int inHeightInch;
	int inWeight;
	string yr;
	Player::YearType inYear;
	//string inYear;
	int inGames;
	double inPPG;
	double inRPG;
	double inAPG;
	double inTOPG;
	
	string fullname;
	string space =  " ";
	
	
	Player tempPlayer;
	for(int i = 0;  i < t.numberPlayers; i++){
		in >> inFirstName >> inLastName;
		in >> letter;
		if (letter == 'G'){
			inPosition  = Player::Guard;
		}
		else if(letter == 'F'){
			inPosition = Player::Forward;
		}
		else if(letter == 'C'){
			inPosition = Player::Center;
		}
		in >> inHeightFt;
		in >> dash;
		in >> inHeightInch;
		in >> inWeight;
		//in >> inYear; 
		in >> yr;
		if (yr == "Junior"){
			inYear = Player::JUNIOR;
		}
		else if(yr == "Freshman"){
			inYear = Player::FRESHMAN;
		}
		else if(yr == "Sophomore"){
			inYear = Player::SOPHOMORE;
		}
		else{
			inYear = Player::SENIOR;
		}
		in >> inGames; 
		in >> inPPG >> inRPG >> inAPG >> inTOPG;
		
		fullname = inFirstName + space + inLastName;
		tempPlayer.assignPlayer(fullname, inPosition, inHeightFt, inHeightInch, inWeight, inYear, inGames, inPPG, inRPG, inAPG, inTOPG);
		t.PlayerArrayPtr[i] = tempPlayer;
	}
}

void Team::teamListTeamSimple(){
	cout << School << " " << Mascot;
}

void Team::teamListTeamComplex(){
	cout << School << " " << Mascot;
	cout << "\n\t";
	cout << "Conference Wins: " << confWins << "\tConference Losses: " << confLoss;
	cout << "\tOverall Wins: " << overallWins << "\tOverall Losses: " << overallLoss;
	cout << "\tNumber of Players: " << numberPlayers;
	cout << "\t\n~~~~~~~~~~~~~\n";
}


void Team::teamListPlayersSimple(){
	for(int i = 0; i < numberPlayers; i++){
		cout << "\t";
		cout << i+1 << ": ";
		cout << PlayerArrayPtr[i].returnFullName();
		cout << endl;
	}
}

void Team::teamListPlayersComplex(){
	for(int i = 0; i < numberPlayers; i++){
		cout << "\t";
		cout << i+1 << ": ";
		cout << PlayerArrayPtr[i].returnFullName();
		cout << endl;
		cout << "\t";
		PlayerArrayPtr[i].displayStats();
		cout << endl;
	}
}

int Team::getNumPlayers(){
	return numberPlayers;
}

Player * Team::teamGetPlayer(int whichPlayer){
	Player * pptr = &(PlayerArrayPtr[whichPlayer-1]);
	return pptr;	
}

bool Team::betterThanTeam(Team * other){
	if(confWins != other->confWins)
	{
		if(confWins > other->confWins){
			return true;
		}
		else{
			return false;
		}
	}
	else{ //if the conference wins are the same, first wont change place
		return false;
	}
	return true; //never will happen
}


void Team::teamDisplayHighestScoringPlayerOfTeam(){
	Player * pptr = teamGetHighScorePlayer();
	cout << pptr->returnFullName();
	cout << endl;
}

Player * Team::teamGetHighScorePlayer(){
	Player * bestPlayer =  &(PlayerArrayPtr[0]);
	int i=0;
	for (i=1; i< numberPlayers; i++){
		if(PlayerArrayPtr[i].returnPPG() > bestPlayer->returnPPG()){
			bestPlayer = &(PlayerArrayPtr[i]);
		}
	}
	return bestPlayer;	
}


void Team::teamDisplayTallestPlayerOfTeam(){
	Player * pptr = teamGetTallestPlayerOfTeam();
	cout << pptr->returnFullName();
	cout << endl;
}

Player * Team::teamGetTallestPlayerOfTeam(){
	Player * tallest =  &(PlayerArrayPtr[0]);
	int i=0;
	for (i=1; i< numberPlayers; i++){
		if(PlayerArrayPtr[i].returnFullHeight() > tallest->returnFullHeight()){
			tallest = &(PlayerArrayPtr[i]);
		}
	}
	return tallest;	
}


