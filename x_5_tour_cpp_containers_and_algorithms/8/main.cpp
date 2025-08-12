#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

ostream& operator<<(ostream& os, const vector<string>& vec)
{
	for (auto el : vec)
	{
		os << el << endl;
	}

	return os;
}

int main() 
{
	vector<string> testVec {"Kant", "Plato", "Aristotle", "Kierkegard", "Hume"};
	cout << testVec;
	cout << endl << "and now sorted:" << endl;
	sort(testVec.begin(), testVec.end());
	cout << testVec;
	return 0;
}
