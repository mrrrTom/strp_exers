#include <iostream>

using namespace std;

int strlen(const char* str) {
	const char* cursor = str;
	int res = 0;
	while (*cursor != '\0') {
		res++;
		cursor++;
	}

	return res;
}

void rev(char* str) {
	int l = strlen(str);
	int max_i = l / 2;
	for (int i = 0; i < max_i; i++ ) {
		char temp = str[i];
		str[i] = str[l - i - 1];
		str[l - i - 1] = temp;
	}
}

int main() {
	char str[7] { 'b', 'r', 'a', 'b', 'u', 's', '\0' };
	cout << str << endl;
	rev(str);
	cout << str << endl;
	return 0;
}
