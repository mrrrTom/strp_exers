#include <iostream>
using namespace std;

int main() {
	unsigned long int i = 0;
	try {
		while(true) {
			int* k = new int[1000000000](3);
			i++;
		}
	}
	catch(const bad_alloc&) {
		cout << "allocated with value: " << (i * (sizeof(int[1000000000]))) << endl;
	}
	catch(...) {
		cout << "smth thrown" << endl;
	}

	return 0;
}
