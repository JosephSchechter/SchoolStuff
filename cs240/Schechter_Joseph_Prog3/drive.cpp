#include <iostream>
#include <string>
#include <fstream>
#include "TownList.h"
#include <cmath>
#include <cstdlib>
#include "Town2.h" 

using namespace std;


int main(int argc, char *argv[]){
	//take input from argv[1]
	if(argc != 2){	//if the call was made
		cout << "Bad number of inputs, you screwed up" << endl;
		return 0;
	
	}
	string infile = argv[1];
	ifstream in;
	in.open(infile.data());

	if(in.fail()){
		cout << "\nBad input file name. EXITING" << endl;
		return 0;
	}
	
	string inTownName = "";
	int loc1 = 0;
	int loc2 = 0;
	
	
	TownList * tl = new TownList;
	while(!in.eof())
	{
		in >> inTownName;
		if(inTownName != ""){
			in >> loc1;
			in >> loc2;
			tl->insert(inTownName, loc1, loc2);
		}
		inTownName = "";		
	}
	//	The number of towns
//	cout << "# of towns: " << tl->getSize()<<endl;
	int numTowns = tl->getSize();





	
	Town2 * townarray = NULL;
	townarray = new Town2[numTowns];
	
	
	
//	Town * twnptr = tl.head;
	Town * twnptr = tl->head;
	
	
	
	for(int i =0; i<numTowns; i++){
		//move data
		inTownName = twnptr->name;
		loc1 = twnptr->x;
		loc2 = twnptr->y;
		
		townarray[i] = Town2(inTownName, loc1, loc2);
		
		twnptr=twnptr->next;
	}
	
	
	delete tl;
	
/*	
	//checking the move, it works
	
	cout << endl;
	cout << "printing town names: ";
	for(int i =0; i< numTowns; i++){
		cout << townarray[i].getName() << " ";
	}
	cout << endl;
*/
	

	//Go through and find all north and south neighbors
	for(int i = 0; i<numTowns; i++)
	{
//		cout << "\nPrinting neighbors for " <<townarray[i].getName() << " ";
		for(int j=0; j<numTowns; j++)
		{
			if(i!=j){
				if(townarray[i].x==townarray[j].x)
				{ //either north or south of eachother
					if(townarray[i].y > townarray[j].y)
					{ //j is SOUTH of i
						if(townarray[i].neighborPos[1] == -1)
						{
							townarray[i].neighborPos[1] = j;
						}
						else if( fabs(townarray[townarray[i].neighborPos[1]].y - townarray[i].y) > fabs(townarray[j].y - townarray[i].y) )
						{ //the new town is closer than previous one in there
							townarray[i].neighborPos[1] = j;
						}
						//if its far out, do nothing
					}
					else if(townarray[i].y < townarray[j].y)
					{ //j is NORTH of i
						if(townarray[i].neighborPos[0] == -1)
						{
							townarray[i].neighborPos[0] = j;
						}
						else if( fabs(townarray[townarray[i].neighborPos[0]].y - townarray[i].y) >  fabs(townarray[j].y - townarray[i].y) )
						{//the new town is closer than previous one in there
							townarray[i].neighborPos[0] = j;
						}
					}
				}
			}
			else{} //looks at self
		}
	}
	
	//Go through and find all east and west neighbors
	for(int i = 0; i<numTowns; i++)
	{
		for(int j=0; j<numTowns; j++)
		{
			if(i!=j)
			{
				if(townarray[i].y==townarray[j].y)
				{ // either east or west of eachother
					if(townarray[i].x > townarray[j].x)
					{	//j is to the WEST of i
						if(townarray[i].neighborPos[3] == -1)
						{
							townarray[i].neighborPos[3] = j;
						}
						else if( fabs(townarray[townarray[i].neighborPos[3]].x - townarray[i].x) >  fabs(townarray[j].x - townarray[i].x)  )
						{
							townarray[i].neighborPos[3] = j;
						}
						//if its further out, do nothing
					}
					else if(townarray[i].x < townarray[j].x)
					{ // j is to the EAST of i
						if(townarray[i].neighborPos[2] == -1)
						{
							townarray[i].neighborPos[2] = j;
						}
						else if( fabs(townarray[townarray[i].neighborPos[2]].x - townarray[i].x) >  fabs(townarray[j].x - townarray[i].x)  )
						{
							townarray[i].neighborPos[2] = j;
						}
						//if its further out, do nothing
					}
				}
			}
			else{}//looks at self
		}
	}

/*	
//Print out all of the neighbors
for(int i =0; i <numTowns; i++){
cout << "\nPrinting neighbors for " <<townarray[i].getName() << " \t\t";
////////////////////////////
	if(townarray[i].neighborPos[0] != -1){
		cout<< "North: " << townarray[townarray[i].neighborPos[0]].getName() << ", \t";
	}
	else{
		cout<< "North: " << "NONE, \t";
	}
////////////////////////////
	if(townarray[i].neighborPos[1] != -1){
		cout<< "South: " << townarray[townarray[i].neighborPos[1]].getName() << ", \t";
	}
	else{
		cout<< "South: " << "NONE, \t";
	}
////////////////////////////
	if(townarray[i].neighborPos[2] != -1){
		cout<< "East: " << townarray[townarray[i].neighborPos[2]].getName() << ", \t";
	}
	else{
		cout<< "East: " << "NONE, \t";
	}
////////////////////////////
	if(townarray[i].neighborPos[3] != -1){
		cout<< "West: " << townarray[townarray[i].neighborPos[3]].getName();
	}
	else{
		cout<< "West: " << "NONE";
	}
}

*/

	//Get the user inputs
	string src;
	int start=-1;
	bool goodSource = false;
	while(goodSource == false)
	{
		cout << "\nEnter source town: ";
		cin >> src;
		for(int i= 0; i<numTowns; i++){
			if(townarray[i].getName() == src){
				goodSource = true;
				start = i;
			}
		}
	}
	src="";
	int end=-1;
	bool goodDest = false;
	while(goodDest == false)
	{
		cout << "\nEnter destination town: ";
		cin >> src;
		for(int i= 0; i<numTowns; i++){
			if(townarray[i].getName() == src){
				goodDest = true;
				end = i;
			}
		}
	}


	if(start == end){
		cout << "You are there already, go nowhere, exiting program" << endl;
		return 0;
	}

	//start is the index of the town you start from(source)
	//end is the target


	//make another array of indexes- like pointers to the array of town2's
	int * Q = NULL;
	Q = new int[numTowns];
	int QSize = numTowns;
	
	for(int i = 0; i<numTowns; i++){
		Q[i]=i; //now there is an array of indexies into the main array of towns, we can access the town through the values in Q[]
	}

	//DIJKSTRA
/*	
 1  function Dijkstra(Graph, source):
 2      for each vertex v in Graph:           // Initializations
 3          dist[v] := infinity               // Unknown distance function from source to v
 4          previous[v] := undefined          // Previous node in optimal path from source
 5      dist[source] := 0                     // Distance from source to source
 
 
 6      Q := the set of all nodes in Graph
        // All nodes in the graph are unoptimized - thus are in Q
 7      while Q is not empty:                 // The main loop
 8          u := vertex in Q with smallest dist[]
 9          if dist[u] = infinity:
10              break                         // all remaining vertices are inaccessible from source
11          remove u from Q
12          for each neighbor v of u:         // where v has not yet been removed from Q.
13              alt := dist[u] + dist_between(u, v) 
14              if alt < dist[v]:             // Relax (u,v,a)
15                  dist[v] := alt
16                  previous[v] := u
17      return dist[]

If we are only interested in a shortest path between vertices source and target, we can terminate the search at line 12 if u = target. Now we can read the shortest path from source to target by iteration:

1  S := empty sequence
2  u := target
3  while previous[u] is defined:
4      insert u at the beginning of S
5      u := previous[u]

*/

	for(int i= 0; i<numTowns; i++){
		//all the distances are already infinity, do it anyway
		townarray[i].dist = 9999999;
		//all the previous ones are undefined, do it anyway
		townarray[i].prev = -1;
	}
	//set the distance from source to source
	townarray[start].dist = 0;


/*
cout << "\nTest4: starting from: " << townarray[start].getName() << endl;
cout << "Test5: the towns in Q: ";
for(int i = 0; i <QSize; i++){
	cout << townarray[Q[i]].getName() << " ";
}
cout << "\n" << endl;
*/



	while(QSize != 0)
	{
/*
cout << "\nTest3 QSize = " << QSize << endl;
cout << "Test6: the towns in Q: ";
for(int i = 0; i <QSize; i++){
	cout << townarray[Q[i]].getName() << " (" << townarray[Q[i]].getX() << ", " << townarray[Q[i]].getY() << ")" << " ";
}
*/



/*
//printing out Q
cout << endl;
cout << "Distances: ";

for(int i = 0; i <numTowns; i++){
	if(i == QSize){
		cout << " | ";
	}
	cout << townarray[Q[i]].getName() << " (" << townarray[Q[i]].getDist() << ")" << " ";
}
cout << endl;
*/



		int uSpot=0;	//uSpot is where it is in Q
		int u = 0;	//u is the vertex on the graph with the smallest distance
	//do a sorting algorithm to find the smallest distance, finds .dist of all items in Q and puts them in order, these values change over time, so we have to do a sort each time

		//sorting in the biggest at the Q[0], smallest at the Q[QSize-1]
//cout << "sorting\n";
		int r = 0;
		int tempint = 0;
		while (r < QSize) {
			if ( (r == 0) || (townarray[Q[r-1]].getDist() >= townarray[Q[r]].getDist()) ){
				r++;
			}
			else {//swap the ints and strings
				tempint = Q[r]; 
				Q[r] = Q[r-1]; 
				Q[--r] = tempint;
			}
		}

		//the smallest distance is 
		int smallestDist = townarray[Q[0]].getDist();
		for(int i =0; i<QSize; i++){
			if(smallestDist > townarray[Q[i]].getDist()){
				uSpot=i; //the place in Q
				u=Q[i]; //the "pointer" to the townarray
				smallestDist = townarray[u].getDist();
			}
			
		}
		
		if(smallestDist >= 9999999){ //no way to get there
//			cout << "\nBreaking, no way to get there\n";
			break;			
		}
		
		//remove u from Q
		//just take uSpot from there, and move all Q's from there, and put it at the end of the shrunken place
		if(uSpot == QSize-1){//its already at the end of the array
			QSize--;
		}

		else{
			for(int i = uSpot; i <= QSize - 2; i++){
				Q[i] = Q[i+1];
			}
			Q[QSize-1] = u;
			//uSpot = QSize-1;
			QSize--;
		}

		if(u == end){
//			cout << "\nReached destination, breaking\n";
			break;
		}
			
		
		
		int alt = 9999999;
		for(int i = 0; i<4; i++){ //each nieghbor of u
			if(townarray[u].neighborPos[i] == -1){ //no neighbor
				//do nothing
			}
			else 
			{//neighbor exists
				int distbtwn = 0;
				if(i == 0 || i == 1){ //N or S
					distbtwn = fabs(townarray[u].y - townarray[townarray[u].neighborPos[i]].y);
				}
				if(i == 2 || i == 3){ //E or W
					distbtwn = fabs(townarray[u].x - townarray[townarray[u].neighborPos[i]].x);
				}
				alt = townarray[u].getDist() + distbtwn;
				
				
				if(alt < townarray[townarray[u].neighborPos[i]].getDist()){
					townarray[townarray[u].neighborPos[i]].dist = alt;
					townarray[townarray[u].neighborPos[i]].prev = u;
				}
			}
/*			This is where i segfault and get free errors, i moved it into the above else statement
			if(alt < townarray[townarray[u].neighborPos[i]].getDist()){
				townarray[townarray[u].neighborPos[i]].dist = alt;
				townarray[townarray[u].neighborPos[i]].prev = u;
			}
*/
		}
	}
	
	if(townarray[end].getPrev() == -1){
		cout << "\ncannot get there, exiting program" << endl;
		return 0;
	}

	
	
	
	
/*	
//printing out Q
cout << endl;
cout << "Distances: ";

for(int i = 0; i <numTowns; i++){
	if(i == QSize){
		cout << " | ";
	}
	cout << townarray[Q[i]].getName() << " (" << townarray[Q[i]].getDist() << ")" << " ";
}
cout << endl;
*/


/*
cout << "\nName all the towns in townarray[]" << endl;
for(int i = 0; i<numTowns; i++){
	cout << townarray[i].getName() << " dist(" << townarray[i].getDist() << ")" << endl;
}
*/


//	cout << "\nGetting the number of steps" << endl;
	int howManySteps = 0;
	int z = end;
	while(townarray[z].prev != -1){
		howManySteps++;
		z= townarray[z].prev;
	}

	
//	cout << "# of steps = " << howManySteps << endl;
	int * directions;
	directions = new int[howManySteps+1]; //it is +1 because there is a spot for starting location

	
	z=end;
	int counter = howManySteps;
	while(counter >= 0){
		directions[counter] = z;
		counter--;
		z=townarray[z].prev;
	}
	
	
//cout << "\nPrinting Directions\n" << endl;
	cout << "\nThe shortest route from " << townarray[start].getName() << " to " <<  townarray[end].getName() << " is:" << endl;
	int amount = 0;
	string dir = "";
	for(int i = 0; i<howManySteps ; i++){
		if(townarray[directions[i]].getX() == townarray[directions[i+1]].getX())
		{
			if(townarray[directions[i]].getY() > townarray[directions[i+1]].getY()){
				dir = "SOUTH";
				amount = townarray[directions[i]].getY() - townarray[directions[i+1]].getY();
			}
			else if(townarray[directions[i]].getY() < townarray[directions[i+1]].getY()){
				dir = "NORTH";
				amount = townarray[directions[i+1]].getY() - townarray[directions[i]].getY();
			}
		}
		else if(townarray[directions[i]].getY() == townarray[directions[i+1]].getY())
		{
			if(townarray[directions[i]].getX() > townarray[directions[i+1]].getX()){
				dir = "WEST";
				amount = townarray[directions[i]].getX() - townarray[directions[i+1]].getX();
			}
			else if(townarray[directions[i]].getX() < townarray[directions[i+1]].getX()){
				dir = "EAST";
				amount  = townarray[directions[i+1]].getX() - townarray[directions[i]].getX();
			}
		}
			
		cout << "Drive " << amount << " mile(s) " << dir << " to " << townarray[directions[i+1]].getName() << endl;
	}

/* 

//Trying to set everything to default easy values in case something is screwing with my values, it still does not work	
for(int i = 0; i<numTowns; i++){
	Q[i]=0;
}
for(int i = 0; i<numTowns; i++){
	townarray[i] = Town2();
}

*/


	delete [] Q;
	Q = NULL;
	delete [] directions;
	directions = NULL;
	delete [] townarray;
	townarray = NULL;

	
	cout << "EXITING"<<endl;
	return 0;
}
