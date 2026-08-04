#include <iostream>
#include <fstream>
using namespace std;

int main (int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		ifstream f_s {argv[i]};
		string file_input;
		while (f_s >> file_input) { cout << file_input << " "; }
	}
	return 0;
}
