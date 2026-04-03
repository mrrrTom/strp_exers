#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define STOP_WORD "Exit"

vector<string> inputs;

void collect_inputs() {
	string input_word;
	do {
		cin >> input_word;
		inputs.push_back(input_word);
	}
	while(input_word != STOP_WORD);
}

void print_words() {
	for (string word : inputs) {
		cout << word << endl;
	}
}

int main() {
	collect_inputs();
	std::sort(inputs.begin(), inputs.end());
	print_words();
};
