#include <iostream>
using namespace std;

int separator = 0;

int f() {
	int local = separator;
	cout << "f: " << local << endl;
	separator++;
	return 1;
}

int s() {
	int local = separator;
	cout << "s: " << local << endl;
	separator++;
	return 1;
}

int summ(int i, int j) { return i + j; }

int main() {
	cout << "f() + s():" << endl;
	int i = f() + s();
	cout << endl;

	cout << "f() < s():" << endl;
	bool a = f() < s();
	cout << endl;

	cout << "summ(f(), s()):" << endl;
	int k = summ(f(), s());
	cout << endl;

	cout << "f() - s():" << endl;
	int z = f() - s();
	cout << endl;

	cout << "s() - f():" << endl;
	int u = s() - f();

	return 0;
}
