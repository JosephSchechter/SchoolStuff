#include "Conference.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#define NUMTEAMS 9

using namespace std;

void mainConf(Conference &c);
void mainTeamSelect(Conference &c);
void mainTeam(Team *t);
void mainPlayerSelect(Team *t);
void mainPlayer(Player *p);

Conference AmericaEast;
int main(int argc, char* argv[]){

ifstream AmericaEastFile;
	string AmericaEastFileName = ""; //name of the text file
	bool goodinput = false;
	do
	{
		cout << "\nINPUT THE CONFERENCE FILE NAME: ";
		cin >> AmericaEastFileName;
		AmericaEastFile.open(AmericaEastFileName.data());
		if (AmericaEastFile.fail())
			cout<< "\nno file found"<<endl;
		else
			goodinput = true;
	} while(goodinput == false);
	AmericaEastFile >> AmericaEast; //read in the AmericaEastFile into AmericaEast

	mainConf(AmericaEast);
	
	cout << "\n\n\t\tDONE WITH PROGRAM" << endl;

	return 0;
}

void mainConf(Conference &c){
	char selection = NULL;
	while(selection != 'Q')
	{
		c.displayConfMode();
		cout << "\nMAKE A SELECTION: ";
		cin >> selection;
		cin.clear();
		cin.ignore(10000, '\n');
		switch (selection)
		{
			case 't':	//list teams names only
				c.confListTeamsSimple();
				break;
			case 'T':	//list teams detailed
				c.confListTeamsComplex();
				break;
			case 's':	//Show the name of the highest scoring player in the conference
				c.confDisplayHighScorePlayer();
				break;
			case 'S':	//Show the name of the highest scoring player in the conference, and switch to enter queries about that player
				c.confDisplayHighScorePlayer();
				mainPlayer(c.confGetHighScorePlayer());
				break;
			case 'h':	//Show the name of the tallest player in the conference
				c.confDisplayTallestPlayer();
				break;
			case 'H':	//Show the name of the tallest player in the conference and switch to enter queries about that player
				c.confDisplayTallestPlayer();
				mainPlayer(c.confGetTallestPlayer());
				break;
			case 'D':	//Drill down to select and enter queries about a particular team
				mainTeamSelect(c);
				break;
			case 'F':	//Enter queries about the first place team
				mainTeam(c.confGetFirstPlaceTeam());
				break;
			case 'Q':	//Quit this program
				break;
			default:	//other input
				cout << "Invalid input, please select from the menu options."<<endl;
				break;
		}
	}
	return;
}

void mainTeamSelect(Conference &c){
	int selection = 9999;
	
	while(selection != 0)
	{
		c.displayTeamSelectMode();
		cout << "\nMAKE A SELECTION: ";
		while(!(cin>>selection))		//test if its an int
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout<< "\nInvalid input, please select from the menu options. "<<endl;
			c.displayTeamSelectMode();
			cout << "\nMAKE A SELECTION: ";
		}
		
		switch (selection)
		{
			case 1:		//team1
			{
				mainTeam(c.getTeam(1));
				break;
			}
			case 2:		//team2
			{
				mainTeam(c.getTeam(2));
				break;
			}
			case 3:
			{
				mainTeam(c.getTeam(3));
				break;
			}
			case 4:
			{
				mainTeam(c.getTeam(4));
				break;
			}
			case 5:
			{
				mainTeam(c.getTeam(5));
				break;
			}
			case 6:
			{
				mainTeam(c.getTeam(6));
				break;
			}
			case 7:
			{
				mainTeam(c.getTeam(7));
				break;
			}
			case 8:
			{
				mainTeam(c.getTeam(8));
				break;
			}
			case 9:
			{
				mainTeam(c.getTeam(9));
				break;
			}
			case 0:		//quit up to previous menu (conference mode)
				break;
			default:
				cout << "Invalid input, please select from the menu options. "<<endl;
				break;
		}
	}
	cin.clear();
	cin.ignore(10000, '\n');
	return;
}

void mainTeam(Team *t){
	char selection = NULL;
	while(selection != 'Q')
	{
		t->displayTeamMode();
		cout << "\nMAKE A SELECTION: ";
		cin >> selection;
		cin.clear();
		cin.ignore(10000, '\n');
		switch (selection)
		{
			case 'I':	//team info
				t->teamListTeamComplex();
				break;
			case 'p':	//players names only
				t->teamListPlayersSimple();
				break;
			case 'P':	//players detailed view
				t->teamListPlayersComplex();
				break;
			case 'D':	//drill down to player select
				mainPlayerSelect(t);
				break;
			case 'S':	//highest scoring player on team
				cout << "\t";
				t->teamDisplayHighestScoringPlayerOfTeam();
//				cout << "\tScored the most points on his Team";
				break;
			case 'H':	//tallest player on team
				cout << "\t";
				t->teamDisplayTallestPlayerOfTeam();
//				cout << "\tis the tallest on his team";
				break;
			case 'Q':	//quit to mainTeamSelect
				break;
			default:
				cout << "Invalid input, please select from the menu options. "<<endl;
				break;
		}
	}
	return;
}

void mainPlayerSelect(Team *t){
	int selection = 9999;
	while(selection != 0)
	{
		t->displayPlayerSelectMode();
		cout << "\nMAKE A SELECTION: ";
		while(!(cin>>selection))		//test if its an int
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout<< "\nInvalid input, please select from the menu options.\n"<<endl;
			t->displayPlayerSelectMode();
			cout << "\nMAKE A SELECTION: ";
		}
		int numplayers = t->getNumPlayers();
		if(selection == 0)
		{
		}
		else if ((selection > numplayers) || (selection < 0))
		{
			cout << "\nInvalid input, please select from the menu options. \n";
		}
		else //good player selection
		{
			mainPlayer(t->teamGetPlayer(selection));
			//selection = 0;
		}

	}
	return;
}

void mainPlayer(Player *p){
	char selection = NULL;
	while(selection != 'Q')
	{
		p->displayPlayerMode();
		cout << "\nMAKE A SELECTION: ";
		cin >> selection;
		cin.clear();
		cin.ignore(10000, '\n');
		switch (selection)
		{
			case 'I': //detailed player info
				cout << "\n\t";
				cout << p->returnFullName();
				cout << "\n\t";
				p->displayStats();
				cout << endl;
				break;
			case 'S': //scoring average
				cout << "\n\t";
				cout << p->returnFullName();
				cout << "\n\tPoints Per Game: ";
				cout << p->returnPPG();
				cout << endl;
				break;
			case 'R': //rebounding average
				cout << "\n\t";
				cout << p->returnFullName();
				cout << "\n\tRebounds Per Game: ";
				cout << p->returnRPG();
				cout << endl;
				break;
			case 'H': //height
				cout << "\n\t";
				cout << p->returnFullName();
				cout << "\n\tHeight: ";
				cout << p->returnHeightFt();
				cout << "' ";
				cout << p->returnHeightInch();
				cout << "\"";
				cout << endl;
				break;
			case 'Q': //quit to prev menu
				break;
			default:
				cout << "Invalid input, please select from the menu options."<<endl;
				break;
		}
	}
}