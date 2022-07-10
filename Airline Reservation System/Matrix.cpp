#include "Matrix.h"

//Constructor
Matrix::Matrix(int size) {
	this->size = size;
	root = new node * [size];
	for (int i = 0; i < size; i++) {
		root[i] = new node[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			root[i][j].isDestination = false;
			root[i][j].hotelCharges = 0;
			root[i][j].Path = -1;
			if (i == j) {
				root[i][j].c = 0;
				root[i][j].t = 0;
			}
			else {
				root[i][j].c = 99999999;
				root[i][j].t = 99999999;
			}
		}
	}

}

//Setting Origin
void Matrix::passOrigin(string origin, int hotelCharges, int index) {
	root[0][index].hotelCharges = hotelCharges;
	root[0][index].location = origin;
	root[index][0].hotelCharges = hotelCharges;
	root[index][0].location = origin;
}

//Generating Graph
void Matrix::generateAdjMatrix(string src, string desti, string date, string fromTime, string toTime, int cost, string airChoice) {

	RouteCharacteristics temp;

	temp.airlineChoice = airChoice;
	temp.cost = cost;
	temp.date = date;
	temp.fromTime = fromTime;
	temp.toTime = toTime;
	bool flag = false;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (root[i]->location == src && root[0][j].location == desti)
			{
				for (int k = 0; k < root[i][j].destination.Size(); k++) {
					if (root[i][j].destination[k] == temp) {
						flag = true;
					}
				}
				if (!flag) {
					root[i][j].isDestination = true;
					temp.hotel = root[0][j].hotelCharges;
					root[i][j].destination.push_back(temp);
				}
			}
		}
	}
}

//Storing Min Values of Time and Cost in Graph
void Matrix::addCostTime() {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (root[i][j].isDestination) {
				root[i][j].c = root[i][j].destination.MinCost();
				root[i][j].t = root[i][j].destination.MinTime();
			}
		}
	}
}

//Floyds Algo for Cost(shortest path)
void Matrix::FloydsAlgoCost() {

	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {

				if (root[i][j].c > root[i][k].c + root[k][j].c) {
					root[i][j].c = root[i][k].c + root[k][j].c;
					root[i][j].Path = k;
				}
			}
		}
	}
}

//Floyds Algo for Time(shortest path)

void Matrix::FloydsAlgoTime() {

	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {

				if (root[i][j].t > root[i][k].t + root[k][j].t) {

					root[i][j].t = root[i][k].t + root[k][j].t;
					root[i][j].Path = k;
				}
			}
		}
	}
}

//Check which one to print acc to input
bool Matrix::CheckPrint(int i, int j, string date, string airline,bool timecheck) {
	bool chkalt = true;
	if (date != "" && airline != "") {
		chkalt = root[i][j].destination.printAirLineDnT(date, airline);
		
	}
	if (date != "" && airline == "") {
		chkalt = root[i][j].destination.printDate(date,timecheck);
	}
	if (date == "" && airline == "") {
		root[i][j].destination.print();
	}
	return chkalt;
}

//Printing Path
void Matrix::PathPrint(int i, int j, string date, string airline,bool timecheck, bool chk) {
	int k = root[i][j].Path;
	bool flag = true;

	if (k == -1) {
		if (!chk) {
			cout << root[i]->location << " to " << root[j]->location << endl;
			CheckPrint(i, j, date, airline,timecheck);
			//	cout << endl << "DIRECT" << endl << endl;
		}
	end:
		return;
	}
	PathPrint(i, k, date, airline,timecheck, true);

	cout << root[i]->location << " to ";
	cout << root[k]->location << endl;

	flag = CheckPrint(i, k, date, airline,timecheck);
	if (!flag) {
		goto end;
	}
	PathPrint(k, j, date, airline,timecheck, true);


	cout << root[k]->location;
	cout << " to " << root[j]->location << endl;

	flag = CheckPrint(k, j, date, airline,timecheck);

	//	cout << endl << "INDIRECT" << endl<<endl;
}

//Scenarios
string Matrix::Scenario1(string src, string dest, string date, string airline) {

		int x = 0, y = 0;

		for (int i = 0; i < size; i++) {
			if (root[i]->location == src) {
				x = i;
			}
			if (root[i]->location == dest) {
				y = i;
			}
		}
		FloydsAlgoCost();
		PathPrint(x, y, date, airline,false);

		cout << "\n^^ Sorted Acc to Cost" << endl;
		date = root[x][y].destination.getNewDate(date);
		return date;
}

string Matrix::Scenario2(string src, string dest, string date) {

	int x = 0, y = 0;

	for (int i = 0; i < size; i++) {
		if (root[i]->location == src) {
			x = i;
		}
		if (root[i]->location == dest) {
			y = i;
		}
	}
	FloydsAlgoTime();
	PathPrint(x, y, date, "",false);

	cout << "\n^^ Sorted Acc to Time" << endl;
	date = root[x][y].destination.getNewDate(date);

	return date;
}

string Matrix::Scenario3(string src, string dest, string date) {

	int x = 0, y = 0;
	for (int i = 0; i < size; i++) {
		if (root[i]->location == src) {
			x = i;
		}
		if (root[i]->location == dest) {
			y = i;
		}
	}

	FloydsAlgoCost();
	PathPrint(x, y, date, "",false);

	date = root[x][y].destination.getNewDate(date);
	return date;

}

string Matrix::Scenario4(string src, string dest, string date, int time) {

	int x = 0, y = 0;
	for (int i = 0; i < size; i++) {
		if (root[i]->location == src) {
			x = i;
		}
		if (root[i]->location == dest) {
			y = i;
		}
	}

	FloydsAlgoTime();
	
	PathPrint(x, y, date, "",true);

	cout << "\n^^ Sorted Acc to Time" << endl;
	date = root[x][y].destination.getNewDate(date);
	return date;
}
string Matrix::Scenario5(string src, string dest, string date) {

	bool direct = false;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (root[i]->location == src && root[i][j].isDestination && root[j]->location == dest) {
				root[i][j].destination.MinCost();
				root[i][j].destination.printDate(date,false);
				direct = true;
				date = root[i][j].destination.getNewDate(date);
			}
		}
	}

	if (!direct) {
		cout << "No Direct Path! SHOWING ALTERNATIVES" << endl << endl;
		int x = 0, y = 0;

		for (int i = 0; i < size; i++) {
			if (root[i]->location == src) {
				x = i;
			}
			if (root[i]->location == dest) {
				y = i;
			}
		}

		FloydsAlgoCost();

	//	for(int i = 0; i < size ; i++)
		PathPrint(x, y, date, "",false);
		date = root[x][y].destination.getNewDate(date);
	}
	
	return date;
}
