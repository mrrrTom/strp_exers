#include <iostream>
using namespace std;

void print(const char** month, int arr_length) {
	const char** cursor = month;
	for(int i = 0; i < arr_length; i++) {
		cout << *cursor << endl;
		cursor++;
	}
}

int main() {
	const char* months[] = { "january",
							 "february",
							 "marth",
							 "april",
							 "may",
							 "june",
							 "july",
							 "august",
						     "september",
							 "october",
							 "november",
							 "december"
							};
	print(months, 12);
	return 0;
}
