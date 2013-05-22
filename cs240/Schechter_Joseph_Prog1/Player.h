#include <iostream>
#include <string>
using namespace std;


class Player{
	public:
		enum PositionType {Guard, Forward, Center};
		enum YearType {FRESHMAN, SOPHOMORE, JUNIOR, SENIOR};

		Player(); //constructor
		
		~Player(); //destructor
		
		Player(const Player & other); //copy constructor
		
		Player(string name, PositionType pos, int hf, int hi, int wt, YearType yr, int g, double p, double r, double a, double to); //value constructor
		
		bool operator>(Player & second); //overloaded >
		
		
		
		
		//display player mode
		void displayPlayerMode();
		
		void assignPlayer(string &inname, PositionType inpos, int inheightF, int inheightI, int inweight, YearType inyear, int ingames, double inppg, double inrpg, double inapg, double intopg); 
		
		double returnPPG();
		double returnRPG();
		
		Player * returnPlayer();
		string returnFullName();
		
		int returnFullHeight();
		void displayStats();
		
		int returnHeightFt();
		int returnHeightInch();
		
	private:
		string FullName;
		PositionType Position;//char Position;
		int HeightFt;
		int HeightInch;
		int Weight;
		YearType Year; //string Year;
		int Games;
		double PPG;
		double RPG;
		double APG;
		double TOPG;
	
	
};
