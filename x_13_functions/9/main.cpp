#include <iostream>
using namespace std;

template <size_t R, size_t C>
void print(const int (&arr)[R][C]) {
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			cout << arr[i][j] << " ";
		}

		cout << endl;
	}
}

template <size_t R, size_t C>
void reverse(int (&arr)[R][C]) {
	for (int i = 0; i <= (R/2); ++i) {
		for (int j = 0; j < C; ++j) {
			int r_i = R - i - 1;
			int r_j = C - j - 1;
			if (i == r_i && j >= r_j) continue;
			int temp = arr[r_i][r_j];
			arr[r_i][r_j] = arr[i][j];
			arr[i][j] = temp;
		}
	}
}
int main () {
	cout << "initial array" << endl;
	int arr[3][5] { { 1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}};
	print(arr);
	reverse(arr);
	cout << "reversed" << endl;
	print(arr);
	return 0;
}
