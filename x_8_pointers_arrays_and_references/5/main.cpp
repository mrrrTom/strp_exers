#include <iostream>
using namespace std;

int get_positions_dif(int* left, int* right) {
	if (!left || !right) throw "wrong input";
	
	int result = abs(right - left);
	return result ? --result : result;
}

int main() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	int* r_ptr = arr + 4;
	cout << *r_ptr << endl;
	cout << get_positions_dif(arr + 1, r_ptr);
	return 0;
}
