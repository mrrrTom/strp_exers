#include <iostream>
#include <string>
using namespace std;

char* itoa(int i, char b[], int trg_length) {
	string result = "";
	int length = 0;
	for(; i > 0; length++) {
		int num = i % 10;
		char symb = '0' + num;
		result = symb + result;
		i = i / 10;
	}

	int k = 0;
	for (; k < length; k++) {
		if (k >= (trg_length-1)) 
			throw runtime_error("char array bond check fail");
		b[k] = result[k];
	}
	
	b[k] = '\0';
	return b;
}


int main() {
	int num;
	cout << "insert integer: ";
	cin >> num;
	char b[10];
	cout << "you inserted: " << itoa(num, b, 10) << endl;
	return 0;
}
