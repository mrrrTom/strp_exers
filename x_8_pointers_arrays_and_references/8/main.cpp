#include <iostream>
#include <string>
using namespace std;

int main() {
	char str[] = "a short string";
	cout << "array size (bytes): " << sizeof(str) << endl;
	string strstr = "a short string";
	cout << "string length: " << strstr.length() << endl;
	return 0;
}
