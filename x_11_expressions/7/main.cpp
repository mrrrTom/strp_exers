#include <iostream>
#include <string>
#include <string.h>

#include <dv_str.hpp>
using namespace std;

int main() {
	char test[5] = {'z', 'a', 'b', 's', '\0'};
	char test2[5] = {'r', 'a', 'r', 's', '\0'};
	cout << "strlen: " << dv_str::strlen(test) << endl;
	cout << "strcmp: " << dv_str::strcmp(test, test2) << endl;
	dv_str::strcpy(test, test2);
	cout << "strcpy: " << test2 << endl;
	return 0;
}
