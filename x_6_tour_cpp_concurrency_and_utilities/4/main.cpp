#include <iostream>
#include <random>
#include <vector>
#include <functional>

using namespace std;

int main()
{
	default_random_engine re {};
	normal_distribution<double> dist (15.0, 5.0);

	vector<int> histogram(30, 0);
	for (int i = 0; i < 1000; ++i)
	{
		double rnd = dist(re);
		if (rnd >= 0 && rnd <= 29)
		{
			int index = rnd;
			++histogram[index];
		}
	}

	for (int k = 0; k < histogram.size(); ++k)
	{
		cout << k << '\t';
		for (int j = 0; j <= histogram[k]; ++j)
		{
			cout << '*';
		}
		
		cout << endl;
	}

	return 0;
}
