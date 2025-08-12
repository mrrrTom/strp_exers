#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream ofs{"numbers"};
	for (int i = 0; i < 300; i++)
	{
		ofs << i << " ";
	}

	return 0;
}
