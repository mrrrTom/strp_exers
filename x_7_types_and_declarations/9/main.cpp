#include <iostream>
#include <map>

using namespace std;

map<const char*, int> types {
	{"bool", sizeof(bool)},
	{"char", sizeof(char)},
	{"short", sizeof(short)},
	{"int", sizeof(int)},
	{"long", sizeof(long)},
	{"long long", sizeof(long long)},
	{"float", sizeof(float)},
	{"double", sizeof(double)},
	{"long double", sizeof(long double)},
	{"unsigned", sizeof(unsigned)},
	{"unsigned long", sizeof(unsigned long)}
};

void print_sizes() {
	for (auto pair = types.begin(); pair != types.end(); pair++) {
		cout << pair -> first << ": " << ((pair -> second) / sizeof(char)) \
			<< endl;
	}
}

int main() {
	print_sizes();
	return 0;
}
