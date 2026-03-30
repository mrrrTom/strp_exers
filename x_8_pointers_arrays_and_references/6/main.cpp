#include <iostream>

using namespace std;
int arr_gl[] = { 1, 2, 3, 4 };

void test_bounds (int* arr) {
	cout << "read and write test:" << endl;

	try {
		for (int i = 0; i < 1000000; i++) {
			cout << "new loop" << endl;
			cout << "i: " << i << endl << "\tread val: " << arr[i] << endl;
			arr[i] = 141;
			cout << "\twrote" << endl;

			cout << "i " << -i << endl << "\tread val: " << arr[-i] << endl;
			arr[-i] = 141;
			cout << "\twrote" << endl;
		}
	}
	catch(...) {
		cout << "smth went wrong" << endl;
	}
}

struct test_s {
	char s;
	int arr[4];
};

int main() {
	int arr_lc[] = { 1, 2, 3, 4 };
	int* arr_na = new int[4] { 1, 2, 3, 4 };
	test_s t {'a', { 1, 2, 3, 4 }};
	test_bounds(arr_lc); //arr_gl, arr_lc, arr_na, t.arr
	return 0;
}
