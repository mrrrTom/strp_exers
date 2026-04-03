#include <iostream>
#include <string>
using namespace std;

#define END_STR '\0'

int count_pairs_str(string src, string key_pair) {
	int res = 0;
	size_t pos = src.find(key_pair, 0);
	while(pos != string::npos) {
		res++;
		pos = src.find(key_pair, pos + 1);
	}

	return res;
}

int count_pairs_char(const char* src, const char* key_pair) {
	const char* cursor = src;
	const char* key_cursor = key_pair;
	bool has_first_match = false;
	int res = 0;
	while (*cursor != END_STR) {
		if (has_first_match) {
			if (*cursor == *key_cursor) res++;
			key_cursor--;
			has_first_match = false;
		}
		else {
			if (*cursor == *key_cursor) {
				has_first_match = true;
				key_cursor++;
			}
		}

		cursor++;
	}
	
	return res;
}

int main() {
	string input_word;
	string input_key;
	cout << "insert string src: ";
	cin >> input_word;
	cout << "\ninsert pair to find: ";
	cin >> input_key;

	int str_counted_pairs = count_pairs_str(input_word, input_key);
	cout << "\nstring params function: " << str_counted_pairs << endl;
	cout << "char params function: " << count_pairs_char(input_word.c_str(),
			input_key.c_str()) << endl;
	return 0;
}
