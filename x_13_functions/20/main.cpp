#include <iostream>

using namespace std;
int factorial(int n) {
	int result = 1;
	for (int i = 1; i <= n; ++i) {
		result *= i;
	}

	return result;
}

int main() {
	cout << "welcome to the factorial calculator!" << endl;
	while(true) {
		cout << "insert your number: ";
		int num;
		cin >> num;
		int result = factorial(num);
		cout << "factorial = " << result << endl << endl;
	}

	return 0;
}
