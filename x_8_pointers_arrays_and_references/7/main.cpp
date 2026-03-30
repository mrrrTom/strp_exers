#include <iostream>
using namespace std;

int first = 4;
int second = 5;

void swap(int* left, int* right) {
	*left = (*left) + (*right);
	*right = (*left) - (*right);
	*left = (*left) - (*right);
}

void swap(int& left, int& right) {
	int temp = left;
	left = right;
	right = temp;
}

void print() {
	cout << "first: " << first << " second: " << second << endl;
}

int main() {
	print();
	cout << "pointers swap!" << endl;
	swap(&first, &second);
	print();
	cout << "references swap!" << endl;
	swap(first, second);
	print();
	return 0;
}
