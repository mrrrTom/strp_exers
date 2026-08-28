#include <iostream>

using namespace std;
char* _key;
int _key_count;
int main (int argc, char *argv[]) {
	if (argc > 1) {
		_key = argv[1];
		char* tmp_cursor = argv[1];
		for (; *tmp_cursor != '\0'; ++tmp_cursor) {
			_key_count++;
		}
	}

	string input;
	while(cin >> input) {
		if (_key_count == 0) {
			cout << input << endl;
			continue;
		}

		for (int i = 0; i < input.length(); ++i) {
			cout << static_cast<char>((input[i] ^ _key[i % _key_count]));
		}

		cout << endl;
	}

	return 0;
}
