#include <iostream>
#include <string>

using namespace std;

int main() {
	string name;
	string age;

	cout << "Please, insert your name: " << endl;
	do {
		cin >> name;
		if (!cin) cout << "wrong input!" << endl;
	}
	while (!cin);

	cout << "your age: ";
	do {
		cin >> age;
		if (!cin) cout << "wrong input!" << endl;
	}
	while (!cin);

    cout << endl << "Hello, " << name << ", you are looking good at the age of " << age << endl;
}
