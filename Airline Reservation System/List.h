#include <iostream>
#include <string>
using namespace std;
template <class T>
class  List {
	int size;  //Size of List
	int Capacity; //Capacity Of List;
	T* vector;   //Pointer to Type Array;

public:

	List() {
		Capacity = 0;
		size = 0;
		vector = 0;
	}
	int find(string key) {   //Find Function
		for (int i = 0; i < size; i++) {
			if (vector[i] == key) {
				return 1;
			}
		}
		return -1;
	}

	void push_back(T obj) {  //Push Back Function
		if (size >= Capacity) {
			reserve(Capacity + 5);
		}
		vector[size++] = obj;
		//	vector[size].fromTime = details;
	}

	void reserve(int capacity) {  //Function to Reserve Data;
		if (vector == 0) {
			size = 0;
			Capacity = 0;
		}
		T* Newbuffer = new T[capacity];
		int l_Size = capacity < size ? capacity : size;
		for (unsigned int i = 0; i < l_Size; i++) {
			Newbuffer[i] = vector[i];
		}
		Capacity = capacity;
		delete[] vector;  //Deleting the old one
		vector = Newbuffer;  //AssingingAddress back;
	}

	void operator=(const List<T>& obj) { //Assignment Operator;
		this->size = obj.size;  //Copying the size;
		this->Capacity = obj.Capacity;  //Copying the capacity;
		for (int i = 0; i < size; i++) {
			vector[i] = obj.vector[i];
		}
	}

	bool operator ==(const List<T>& obj) {
		if (size == obj.size) {
			for (int i = 0; i < size; i++) {
				if (vector[i] != obj.vector[i]) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
	T& operator[](int index) {   //Index Operator;
		return vector[index];
	}
	int Size() const {   //Size Function to Return the size of Array;
		return size;
	}

//Sorts list on the basis of Cost
	int MinCost() {
		T temp;
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (vector[i].cost > vector[j].cost) {
					temp = vector[i];
					vector[i] = vector[j];
					vector[j] = temp;
				}
			}
		}
		return vector[0].cost;
	}

//Sorts list on the basis of Time
	int MinTime() {

		int* srchours = new int[size];
		int* desthours = new int[size];
		int* srcmins = new int[size];
		int* destmins = new int[size];
		string hours = "", mins = "";
		string srctemp = "", desttemp = "";
		int retsrchrs, retdesthrs, retsrcmins, retdestmins;
		bool flag = true;

		for (int i = 0; i < size; i++) {

			srctemp = vector[i].fromTime;
			desttemp = vector[i].toTime;

			for (int j = 0; srctemp[j] != '\0'; j++) {
				if (srctemp[j] != ':' && flag) {
					hours += srctemp[j];
				}
				else {
					flag = false;
				}
				if (srctemp[j] != ':' && !flag) {
					mins += srctemp[j];
				}
			}

			srchours[i] = stoi(hours);
			srcmins[i] = stoi(mins);
			flag = true;
			hours = "";
			mins = "";

			for (int j = 0; desttemp[j] != '\0'; j++) {
				if (desttemp[j] != ':' && flag) {
					hours += desttemp[j];
				}
				else {
					flag = false;
				}
				if (desttemp[j] != ':' && !flag) {
					mins += desttemp[j];
				}
			}

			desthours[i] = stoi(hours);
			destmins[i] = stoi(mins);
			flag = true;
			hours = "";
			mins = "";
		}

		T temp;
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (srchours[i] <= desthours[i]) {
					if (abs((srchours[i] - desthours[i])) >= abs((srchours[j] - desthours[j]))) {
						temp = vector[i];
						vector[i] = vector[j];
						vector[j] = temp;
					}
				}
				else {
					if ( (24 - abs((srchours[i] - desthours[i]))) >=  ( 24 - abs((srchours[j] - desthours[j])))) {
						temp = vector[i];
						vector[i] = vector[j];
						vector[j] = temp;
					}
				}
			}
		}

		srctemp = vector[0].fromTime;
		desttemp = vector[0].toTime;

		for (int j = 0; srctemp[j] != '\0'; j++) {
			if (srctemp[j] != ':' && flag) {
				hours += srctemp[j];
			}
			else {
				flag = false;
			}
			if (srctemp[j] != ':' && !flag) {
				mins += srctemp[j];
			}
		}

		retsrchrs = stoi(hours);
		retsrcmins = stoi(mins);
		flag = true;
		hours = "";
		mins = "";

		for (int j = 0; desttemp[j] != '\0'; j++) {
			if (desttemp[j] != ':' && flag) {
				hours += desttemp[j];
			}
			else {
				flag = false;
			}
			if (desttemp[j] != ':' && !flag) {
				mins += desttemp[j];
			}
		}

		retdesthrs = stoi(hours);
		retdestmins = stoi(mins);

		if (retsrchrs > retdesthrs) {
			return (24 - abs((retsrchrs - retdesthrs)));
		}
		else {
			return abs((retsrchrs - retdesthrs));
		}
	}

//Checks Date of source and destination
	int CheckDate(string src,int count) {
		string temp = "";
		string year = "", month = "", day = "";
		int srcy = 0, srcm = 0, srcd = 0, desty = 0, destm = 0, destd = 0;
		bool checkM = false, checkY = false;


		temp = src;
		for (int i = 0; temp[i] != '\0'; i++) {
			if (temp[i] != '/' && !checkM && !checkY) {
				day += temp[i];
			}
			else if (temp[i] == '/' && !checkM && !checkY) {
				checkM = true;
				continue;
			}
			if (temp[i] != '/' && checkM && !checkY) {
				month += temp[i];
			}
			else if (temp[i] == '/' && checkM && !checkY) {
				checkY = true;
				continue;
			}
			if (checkY) {
				year += temp[i];
			}
		}
		// DD/MM/YYYY

		srcy = stoi(year);
		srcm = stoi(month);
		srcd = stoi(day);

		//cout << srcd << " " << srcm << " " << srcy << endl;

		year = "";
		month = "";
		day = "";
		checkM = false;
		checkY = false;

		
		temp = vector[count].date;
		for (int i = 0; temp[i] != '\0'; i++) {
			if (temp[i] != '/' && !checkM && !checkY) {
				day += temp[i];
			}
			else if (temp[i] == '/' && !checkM && !checkY) {
				checkM = true;
				continue;
			}
			if (temp[i] != '/' && checkM && !checkY) {
				month += temp[i];
			}
			else if (temp[i] == '/' && checkM && !checkY) {
				checkY = true;
				continue;
			}
			if (checkY) {
				year += temp[i];
			}
		}
		// DD/MM/YYYY
		desty = stoi(year);
		destm = stoi(month);
		destd = stoi(day);

		//	cout << destd << " " << destm << " " << desty << endl;

		if (srcy <= desty) {
			if (srcm <= destm) {
				if (srcd <= destd) {
					if (srcd == destd) {
						return 1;
					}
					else {
						return 2;
					}
				}
				else {
					if (abs(srcd - destd) == 1 || abs(srcd - destd) == 2) {
						return 2;
					}
					else {
						return 0;
					}
				}
			if (srcm == destm) {
				return 1;
			}
		}
		else {
			return 0;
		}
	}
	return false;
}
	
	string getNewDate(string old) {
		int chk = 0;
		for (int i = 0; i < size; i++) {
			chk = CheckDate(old, i);
			if (chk == 1) {
				return vector[i].date;
			}
		}

		return old;
	}

//Printing ---vvv---
	void print() {
		
		for (int i = 0; i < size; i++) {
			cout << vector[i].date << " " << vector[i].fromTime << " " << vector[i].toTime << " " << vector[i].cost << " " << vector[i].airlineChoice << endl;
		}
		cout << endl;
	}

	bool printDate(string date, bool timecheck) {
		int chk = 0;
		bool display = true,same = false, alt = false;
		if (!timecheck) {
			for (int i = 0; i < size; i++) {
				chk = CheckDate(date, i);
				if (chk == 1 && display) {
					cout << "--------------------------------\n";
					cout << "Date: " << vector[i].date << "\n" << "Departure: " << vector[i].fromTime << "\n" << "Arrival: " << vector[i].toTime << "\n" << "Cost: " << vector[i].cost << "\n" << "Airline: " << vector[i].airlineChoice << endl;
					cout << endl;
					same = true;
				//	display = false;
				}
			}
		}
		if (!same) {
			cout << "No flight on given date. Alternatives: " << endl << endl;
			for (int i = 0; i < size; i++) {
				chk = CheckDate(date, i);
				if (chk == 2 && display) {
					cout << "--------------------------------\n";
					cout << "Date: " << vector[i].date << "\n" << "Departure: " << vector[i].fromTime << "\n" << "Arrival: " << vector[i].toTime << "\n" << "Cost: " << vector[i].cost << "\n" << "Airline: " << vector[i].airlineChoice << endl;
					cout << endl;
					alt = true;
					//display = false;
				}
			}
			if (!alt) {
				cout << "No Alternatives." << endl;
			}
			else {
				cout << endl;
				cout << "Hotel Charges: " << vector[0].hotel << endl;
			}
			return alt;
		}
		return true;
	}

	bool printAirLineDnT(string date, string airline) {
		int chk = 0;
		bool same = false, display = true, alt = false;
		for (int i = 0; i < size; i++) {
			chk = CheckDate(date, i);
			if ((vector[i].airlineChoice == airline) && (chk == 1) && (display)) {
				cout << "-------------------------------\n";
				cout << "Date: " << vector[i].date << "\n" << "Departure: " <<vector[i].fromTime << "\n" << "Arrival: " << vector[i].toTime << "\n" << "Cost: " << vector[i].cost << "\n" << "Airline: " << vector[i].airlineChoice << endl;
				same = true;
			//	display = false;
				cout << endl;
			}
		}
		if(!same){
			cout << "No flight on given date. Alternatives: " << endl << endl;
			for (int i = 0; i < size; i++) {
				chk = CheckDate(date, i);
				if ((vector[i].airlineChoice == airline) && (chk == 2) &&(display)) {
					cout << "-------------------------------\n";
					cout << "Date: " << vector[i].date << "\n" << "Departure: " << vector[i].fromTime << "\n" << "Arrival: " << vector[i].toTime << "\n" << "Cost: " << vector[i].cost << "\n" << "Airline: " << vector[i].airlineChoice << endl;
					cout << endl;
					alt = true;
					//display = false;
				}
			}
			if (!alt) {
				cout << "No alternatives." << endl;
			}
			else {
				cout << endl;
				cout << "Hotel Charges: " << vector[0].hotel << endl;
			}
			return alt;
		}
		return true;
	}
};
