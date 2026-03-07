#include <iostream>

using namespace std;

int main() {
	long long int array = 1217060504;
	while(array) {
		cout << (array % 100) << endl;
		array = array / 100;
	}

	return 0;
}
