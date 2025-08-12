#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	ifstream is {"numbers"};
	int temp = 0;
	while (!is.eof())
	{
		is >> temp;
		cout << temp;
	}

	return 0;
}
