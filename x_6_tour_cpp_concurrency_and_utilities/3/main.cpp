#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono_literals;
int main()
{
	double summ {0};
	int i = 0;
	auto start = std::chrono::high_resolution_clock::now();
	while (i++ < 1000)
	{
		auto end = std::chrono::high_resolution_clock::now();
		double elapsed = std::chrono::duration<double>(end - start).count();
		start = end;
		summ += elapsed;
	}

	cout << endl << (summ/1000);
}
