#include <iostream>
#include <vector>
using namespace std;

void copy(int* start, int* end, vector<int>& tgt) {
	int* cursor = start;
	while (cursor != end) {
		tgt.push_back(*cursor);
		cursor++;
	}
}

int main() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	vector<int> tgt;

	copy(arr, &arr[9], tgt);

	for(int val : tgt) {
		cout << val << endl;
	}

	return 0;
}
