#include <iostream>
#include <math.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include "Matrix.h"
#define Islamabad 1
using namespace std;

//file read;
string* readHotelCharges_perday_only_cities(string str, int& count, Matrix& obj) {
	string* HotelCharges_perday_only_cities = new string[20];
	ifstream reads;
	string a;
	reads.open(str);
	while (getline(reads, a)) {
		string origin = "";
		string temp = "";
		for (int i = 0; a[i] != '\0'; i++) {
			if (a[i] == ' ') {
				origin = temp;
			}
			else {
				temp = temp + a[i];
			}
		}

		obj.passOrigin(origin, stoi(a.erase(0, origin.length() + 1)), count);
		count++;

	}
	return HotelCharges_perday_only_cities;
}
//2nd file read;
void readFlights(string str, Matrix& obj) {
	ifstream reads;
	string flights;
	int count = 0;
	reads.open(str);

	while (getline(reads, flights)) {
		count = 0;
		string source;
		string desti;
		string date;
		string fromTime;
		string toTime;
		string temp2;
		int cost = 0;
		string airlineName;
		string temp;
		for (int i = 0; flights[i] != '\0'; i++) {
			if (flights[i] == ' ') {

				count++;
				if (count == 1) {
					source = temp;
					temp = "";
				}
				else if (count == 2) {
					desti = temp;
					temp = "";

				}
				else if (count == 3) {
					date = temp;
					temp = "";

				}
				else if (count == 4) {
					fromTime = temp;
					temp = "";

				}
				else if (count == 5) {
					toTime = temp;
					temp = "";

				}
				else if (count == 6) {
					cost = stoi(temp);
					temp2 = temp;

				}
			}
			else {
				temp = temp + flights[i];
			}
		}

		flights.erase(0, source.length() + 1 + desti.length() + 1 + date.length() + 1 + fromTime.length() + 1 + toTime.length() + 1 + temp2.length() + 1);
		obj.generateAdjMatrix(source, desti, date, fromTime, toTime, cost, flights);
	}
}

//main Starts here;
int main() {

	
	int citiesCount = 0;
	int routes = 0;
	Matrix generateMatrix(11);  //We have only 10 cities at the moment;
	readHotelCharges_perday_only_cities("HotelCharges_perday.txt", citiesCount, generateMatrix);
	readFlights("Flights.txt", generateMatrix);
	generateMatrix.addCostTime();

	string P1;
	string P2;
	int slt1;
	int slt2;
	string stop;
	char temp;
	string plane;
	string date;
	int time;


	cout << "Enter your location: ";
	cin >> P1;

	cout << "Enter your  destination: ";
	cin >> P2;

	cout << "Enter Date(DD/MM/YYYY): ";
	cin >> date;

	bool checkplane = false;
	cout << "Do you want Airline of your choice?:(y/n)";
	cin >> temp;
	if (temp == 'y' || temp == 'Y') {
		cout << "Which One?\n";
		cin >> plane;
		checkplane = true;
	}

	bool checkstop = false;
	cout << "Do you want to add stop?{y/n)";
	cin >> temp;
	
Stop1:
	if (temp == 'y' || temp == 'Y') {
		cout << "To where?\n";
		cin >> stop;
		checkstop = true;
	}
	bool timecheck = false;
	if (!checkplane) {
		if (checkstop) {
			cout << "Do you want to add transit time?{y/n)";
			cin >> temp;
			if (temp == 'y' || temp == 'Y') {
				cout << "How many hours?\n";
				cin >> time;
				timecheck = true;
			}
		}
	}

	cout << "What Facility you want?\n";
	cout << "(1)Less Expenditure -OR- (2)Less Travel Time -OR- (3) None:\n";
	cin >> slt2;

		if (slt2 == 1) {

			if (checkplane) {
				cout << endl << endl;
				if (checkstop) {
					date = generateMatrix.Scenario1(P1, stop, date, plane);
					checkstop = false;
					cout << "Do you want to add another stop?{y/n)\n";
					cin >> temp;
					if (temp == 'y' || temp == 'Y') {
						P1 = stop;
						goto Stop1;
						
					}
					else {
						P1 = stop;
						date = generateMatrix.Scenario1(P1, P2, date, plane);
						goto EndFlight;
					}
				}
			}
			else {
					if (checkstop) {
						date = generateMatrix.Scenario3(P1, stop, date);
						checkstop = false;
						cout << "Do you want to add another stop?{y/n)\n";
						cin >> temp;
						if (temp == 'y' || temp == 'Y') {
							P1 = stop;
							goto Stop1;
						}
						else {
							P1 = stop;
							date = generateMatrix.Scenario3(P1, P2, date);
							goto EndFlight;
						}
					}
					else {
						date = generateMatrix.Scenario5(P1, P2, date);
						goto EndFlight;
					}
			}
		}

		else if (slt2 == 2) {
			cout << endl << endl;
			
				if (timecheck && checkstop) {
					date = generateMatrix.Scenario4(P1, stop, date,time);

					checkstop = false;
					cout << "Do you want to add another stop?{y/n)\n";
					cin >> temp;
					if (temp == 'y' || temp == 'Y') {
						P1 = stop;
						goto Stop1;
					}
					else {
						P1 = stop;
						date = generateMatrix.Scenario4(P1, P2, date, time);
						goto EndFlight;
					}
				}
				else if (!timecheck && checkstop) {
					date = generateMatrix.Scenario2(P1, stop, date);

					checkstop = false;
					cout << "Do you want to add another stop?{y/n)\n";
					cin >> temp;
					if (temp == 'y' || temp == 'Y') {
						P1 = stop;
						goto Stop1;
					}
					else {
						P1 = stop;
						date = generateMatrix.Scenario2(P1, P2, date);
						goto EndFlight;
					}
				}
				else {
					date = generateMatrix.Scenario2(P1, P2, date);
					goto EndFlight;
				}
		}

		else {
			if (!checkstop) {
				cout << endl << endl;
				date = generateMatrix.Scenario5(P1, P2, date);
				goto EndFlight;
			}
			else {
				cout << endl << endl;
				if (timecheck) {
					date = generateMatrix.Scenario4(P1, stop, date, time);

					checkstop = false;
					cout << "Do you want to add another stop?{y/n)\n";
					cin >> temp;
					if (temp == 'y' || temp == 'Y') {
						P1 = stop;
						goto Stop1;
					}
					else {
						P1 = stop;
						date = generateMatrix.Scenario4(P1, P2, date, time);
						goto EndFlight;
					}
				}
				else {
					date = generateMatrix.Scenario3(P1, stop, date);

					checkstop = false;
					cout << "Do you want to add another stop?{y/n)\n";
					cin >> temp;
					if (temp == 'y' || temp == 'Y') {
						P1 = stop;
						goto Stop1;
					}
					else {
						P1 = stop;
						date = generateMatrix.Scenario3(P1, P2, date);
						goto EndFlight;
					}
				}
			}
		}
	EndFlight:
		cout << endl << endl << "Journey Ended. Thanks for Travelling" << endl;

	return 0;
}