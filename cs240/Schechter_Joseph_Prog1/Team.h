#include "Player.h"
#include <iostream>
#include <string>
using namespace std;


class Team{
	public:
		Team();
		~Team();
		
		//display team mode
		void displayTeamMode();
		//player selection mode
		void displayPlayerSelectMode();
		
		bool operator>(Team & second); //overloaded >
		
		
		friend std::istream& operator>>(std::istream& in, Team & t);
		
		//Prints out the Name of the Team and Mascot
		void teamListTeamSimple();
		//Prints out All the data about the Team
		void teamListTeamComplex();
		
		//Prints out the Names of All the Players on the Team
		void teamListPlayersSimple();
		//Prints out the Names and other data of All the Players on the Team
		void teamListPlayersComplex();
		
		//returns the number of players on the team
		int getNumPlayers();
		//returns a pointer to a Player
		Player * teamGetPlayer(int whichPlayer);
		
		//Tests if a team has more conference teams than the other team
		bool betterThanTeam(Team * other);
		
		//Prints out the Player Name of the highest scoring player on the team
		void teamDisplayHighestScoringPlayerOfTeam();
		//Returns a pointer to the Highest Scoring Player on a team
		Player * teamGetHighScorePlayer();
		
		//Prints out the Player Name of the Tallest Player on a Team 
		void teamDisplayTallestPlayerOfTeam();
		//returns a pointer to the Tallest Player on a Team
		Player * teamGetTallestPlayerOfTeam();
		
		
	private:
		string School;
		string Mascot;
		int confWins;
		int confLoss; 
		int overallWins;
		int overallLoss;
		int numberPlayers;
		Player * PlayerArrayPtr;


};
