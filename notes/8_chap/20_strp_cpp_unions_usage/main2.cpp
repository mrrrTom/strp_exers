#include <iostream>
using namespace std;

int main() {
	for (int i = 0; i < 1000000; i++) {
		long val = (rand() % 32769);
		if (val == 32763) { val = 3000000000; }
		cout << 1 << ' ' << val << endl;
	}

	return 0;
}
