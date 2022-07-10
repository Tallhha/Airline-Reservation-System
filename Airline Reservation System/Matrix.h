#include "List.h"
#include <iostream>
using namespace std;
#include <string>

//List
struct RouteCharacteristics {
	string date;
	string fromTime;
	string toTime;
	int cost;
	int hotel;
	string airlineChoice;

	bool operator == (RouteCharacteristics& obj) {
		if (hotel == obj.hotel && date == obj.date && fromTime == obj.fromTime && toTime == obj.toTime && cost == obj.cost && airlineChoice == obj.airlineChoice) {
			return true;
		}
		return false;
	}

	RouteCharacteristics& operator = (RouteCharacteristics& obj) {

		date = obj.date;
		fromTime = obj.fromTime;
		toTime = obj.toTime;
		cost = obj.cost;
		airlineChoice = obj.airlineChoice;
		hotel = obj.hotel;

		return *this;
	}

};
struct node {
	string location;
	List<RouteCharacteristics>destination;
	int hotelCharges;
	bool isDestination;
	int c, t; //cost,time
	int Path;
};
class Matrix {
	node** root;
	int size;

public:
//Generating Graph
	Matrix(int);
	void passOrigin(string, int, int);
	void generateAdjMatrix(string src, string desti, string, string, string, int, string);
	void addCostTime();

//Shortest Paths acc. to Time/Cost
	void FloydsAlgoCost();
	void FloydsAlgoTime();

//For Paths Printing
	void PathPrint(int i, int j, string date, string airline,bool timecheck, bool chk = false);
	bool CheckPrint(int i, int j, string date, string airline, bool timecheck = false);

//Scenarios 1,2,3,4,5
	string Scenario1(string src, string dest, string date, string airline);
	string Scenario2(string src, string dest, string date);
	string Scenario3(string src, string dest, string date);
	string Scenario4(string src, string dest, string date, int time);
	string Scenario5(string src, string dest, string date);

};
