#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

int convert_to_dec(const char* const symb) {
	int num = (*symb) - '0';
	if (num > 9 || num < 0) throw runtime_error("wrong input");
	return num;
}

int convert_to_oct(const char* const symb) {
	int num = (*symb) - '0';
	if (num > 7 || num < 0) throw runtime_error("wrong input");
	return num;
}

int convert_to_hex(const char* const symb) {
	int num = (*symb) - '0';
	if (num <= 9 && num >= 0) return num;
	int num2 = (*symb) - 'A';
	if (num2 >= 0 && num2 <= 5) return (num2 + 10);
	int num3 = (*symb) - 'a';
	if (num3 >= 0 && num3 <= 5) return (num3 + 10);
	throw runtime_error("wrong input");
}

int collect_numbers(const char* src, int base, 
		int (*convert_num)(const char* const)) {
	int result = 0;
	const char* cursor = src;
	while(*cursor != '\0') {
		result = result * base + convert_num(cursor);
		cursor++;
	}

	return result;
}

int atoi(const char* src) {
	const char* cursor = src;
	if (*cursor == '0') {
		cursor++;
		if (*cursor == 'x') { 
			return (collect_numbers((src + 2), 16, convert_to_hex));
		}
		else {
			return (collect_numbers((src + 1), 8, convert_to_oct));
		}
	}
	else {
		return (collect_numbers(src, 10, convert_to_dec));
	}
}

int main() {
	string input;
	cout << "Insert int string for converting: " ;
	cin >> input;
	
	cout << "Converted: " << atoi(input.c_str()) << endl;
	return 0;
}
