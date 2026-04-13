#include <iostream>
#include <string>
using namespace std;

char* itoa(int i, char b[]) {
	string result = "";
	int length = 0;
	for(; i > 0; length++) {
		int num = i % 10;
		char symb = '0' + num;
		result = symb + result;
		i = i / 10;
	}

	for (int k = 0; k < length; k++) {
		b[k] = result[k];
	}

	return b;
}


int main() {
	int num;
	cout << "insert integer: ";
	cin >> num;
	char b[10];
	cout << "you inserted: " << itoa(num, b) << endl;
	return 0;
}
