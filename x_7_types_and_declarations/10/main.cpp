#include <iostream>
#include <map>

using namespace std;

map<const char*, int> types {
	{"bool", alignment_of<bool>::value},
	{"char", alignment_of<char>::value},
	{"short", alignment_of<short>::value},
	{"int", alignment_of<int>::value},
	{"long", alignment_of<long>::value},
	{"long long", alignment_of<long long>::value},
	{"float", alignment_of<float>::value},
	{"double", alignment_of<double>::value},
	{"long double", alignment_of<long double>::value},
	{"unsigned", alignment_of<unsigned>::value},
	{"unsigned long", alignment_of<unsigned long>::value}
};

void print_alignes() {
	for (auto pair = types.begin(); pair != types.end(); pair++) {
		cout << pair -> first << ": " << ((pair -> second) / sizeof(char)) \
			<< endl;
	}
}

int main() {
	print_alignes();
	return 0;
}
