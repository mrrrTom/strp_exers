#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<<(ostream& os, const vector<int>& vec)
{
	for (auto el : vec)
	{
		os << el << endl;
	}

	return os;
}

int main() 
{
	vector<int> testVec {5, 9, -1, 200, 0};
	cout << testVec;
	cout << endl << "and now sorted:" << endl;
	sort(testVec.begin(), testVec.end());
	cout << testVec;
	return 0;
}
