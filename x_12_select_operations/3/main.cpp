#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long unsigned int sum_w_for(vector<int>& v, int length) {
	long long unsigned int result{0};
	for (int i = 0; i < length; i++) result += v[i];
	return result;
}

long long unsigned int sum_w_range_for(vector<int>&v) {
	long long unsigned int result{0};
	for (int i : v) result += i;
	return result;
}

long long unsigned int sum_w_foreach(vector<int>&v) {
	long long unsigned int result{0};
	for_each(&v[0], &v[v.size()-1], 

int main() {

	vector<int> v { 1, 2, 3, 4, 5, 6 };
	cout << sum_w_for(v, v.size()) << endl;
	cout << sum_w_range_for(v) << endl;
	return 0;
}
