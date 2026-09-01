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

	char symb;
	int i = 0;
	while(cin.get(symb)) {
		if (_key_count == 0) {
			cout << symb;
			continue;
		}

		cout << static_cast<char>((symb ^ _key[i % _key_count]));
		i++;
	}

	return 0;
}
