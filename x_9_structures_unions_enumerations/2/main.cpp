#include <iostream>
using namespace std;

char months [][15] = {    "january",
						"february",
						"march",
						"april",
						"may",
						"june",
						"july",
						"augoust",
						"september",
						"october",
						"november",
						"december"
					};
int month_l [] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 

void print_month_length_from_arrays() {
	for (int i = 0; i < 12; i++) {
		cout << months[i] << ": " << month_l[i] << endl;
	}
}

struct month {
	string name;
	short days_count;
};

month months_s [] = { {"january", 31},
					  {"february", 28},
					  {"march", 31},
					  {"april", 30},
					  {"may", 31},
					  {"june", 30},
					  {"july", 31},
					  {"august", 31},
					  {"september", 30},
					  {"october", 31},
					  {"november", 30},
					  {"december", 31}
					};

ostream& operator << (ostream& os, month& m) {
	return (os << m.name << ": " << m.days_count << endl);
}

void print_month_length_from_structs() {
	for (int i = 0; i < 12; i++) {
		cout << months_s[i];
	}
}

int main() {
	cout << "print months`s lengths from arrays:" << endl;
	print_month_length_from_arrays();
	cout << endl;

	cout << "print months`s lengths from structs:" << endl;
	print_month_length_from_structs();
	return 0;
}
