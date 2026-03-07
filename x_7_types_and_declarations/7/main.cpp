#include <iostream>
using namespace std;

void print_symb_range_ascii(char first, char last) {
	for (int i = 0; i <= (last - first); i++) {
		char c = (first + i);
		cout << c << " integer representation: " << dec << ((int)c) << 
			" hexadecimal representation: " << hex << ((int)c) << endl;
	}
}

int main() {
	print_symb_range_ascii('a', 'z');
	print_symb_range_ascii('0', '9');
	print_symb_range_ascii('A', 'Z');
	return 0;
}
