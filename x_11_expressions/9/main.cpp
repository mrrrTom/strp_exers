#include <iostream>

using namespace std;
#define STRING_END '\0'

int strlen(const char* left) {
	int result = 0;
	const char* cursor = left;
	while (*cursor != STRING_END) {
		result++;
		cursor++;
	}
	
	return result;
}

char* cat(const char* left, const char* right) {
	int lsize = strlen(left);
	int rsize = strlen(right);
	int nsize = lsize + rsize + 1;
	char* res = new char[nsize];
	for (int i = 0; i < (nsize - 1); i++) {
		if (i < lsize) {
			res[i] = left[i];
		}
		else {
			res[i] = right[(i - lsize)];
		}
	}

	res[nsize - 1] = STRING_END;
	return res;
}

int main() {
	const char* str_l { "lala" };
	const char* str_r { "rara" };
	char* summ = cat(str_l, str_r);
	cout << summ;
	delete(summ);
	return 0;
}
