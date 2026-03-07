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

const char* get_smallest(map<const char*, int>* inp_types) {
	const char* result;
	int result_val = 10;
	for (auto pair = (*inp_types).begin(); pair != (*inp_types).end(); pair++) {
		if ((pair -> second) < result_val) {
			result_val = pair -> second;
			result = pair -> first;
		}
	}

	return result;
}

const char* get_biggest() {
	const char* result;
	int result_val = 0;
	for (auto pair = types.begin(); pair != types.end(); pair++) {
		if ((pair -> second) > result_val) {
			result_val = pair -> second;
			result = pair -> first;
		}
	}

	return result;
}

int main() {
	cout << "smallest: " << get_smallest(&types) << endl;
	cout << "biggest: " << get_biggest() << endl;
	return 0;
}
