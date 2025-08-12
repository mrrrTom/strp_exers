#include <iostream>
#include <string>

using namespace std;

struct user {
	string name;
	int age;
};

ostream& operator<<(ostream& os, const user& u)
{
	os << "Hello, " << u.name << ", you are looking good at the age of " << u.age << endl;
	return os;
}

istream& operator>>(istream& is, user& u)
{
	string name;
	int age;
	cout << "Please, insert your name: " << endl;
	do {
		is >> name;
		if (!is) cout << "wrong input!" << endl;
	}
	while (!is);

	cout << "your age: ";
	do {
		is >> age;
		if (!is) cout << "wrong input!" << endl;
	}
	while (!is);
	u = {name, age};
	return is;
}

int main() {
	user u;
	cin >> u;
	cout << u;
}
