#include "Team.h"
#include <iostream>
#include <string>
#define NUMTEAMS 9
//using namespace std;


class Conference{
	public:
		Conference(); //default constructor
		~Conference();//destructor
		Conference(const Conference & other); //copy constructor
		
		
		
		void displayConfMode();//display conference mode
		
		void displayTeamSelectMode();//team selection mode
		
		
		friend std::istream& operator>>(std::istream& in, Conference & conf);
		
		Team * getTeam(int number);
		
		
		void confListTeamsSimple();
		void confListTeamsComplex();
		
		Team * confGetFirstPlaceTeam();
		
		void confDisplayHighScorePlayer();
		Player * confGetHighScorePlayer();
		void confDisplayTallestPlayer();
		Player * confGetTallestPlayer();
		
		
		
	private:
		//an array of 9 teams
		Team TeamArray[NUMTEAMS];
//		int privatedata;

		
};
