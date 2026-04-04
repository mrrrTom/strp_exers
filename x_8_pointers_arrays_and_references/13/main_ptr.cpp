#include <iostream>
using namespace std;

int main() {
	int arr[5] = { 1, 2, 3, 4, 5 };
	for (int* i = arr; i < (i + 5); i++) {
		*i = 6;
	}

	return 0;
}
