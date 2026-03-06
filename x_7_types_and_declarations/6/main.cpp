#include <iostream>
using namespace std;

int main() {
	cout << "size of int: " << sizeof(int) << endl;
	cout << "size of double: " << sizeof(double) << endl;
	int a = 3;
	int* ap = &a;
	cout << "size of int*: " << sizeof(ap) << endl;
	return 0;
}
