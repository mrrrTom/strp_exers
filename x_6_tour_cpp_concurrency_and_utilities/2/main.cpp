#include <thread>
#include <iostream>

using namespace std;
using namespace std::chrono;

void f3()
{
	while (true) {
		this_thread::sleep_for(1s);
		cout << "hello " << endl;
	}
}

void f4()
{
	while (true) {
		this_thread::sleep_for(1s);
		cout << "world! " << endl;
	}
}


int main()
{
	thread t3{f3};
	thread t4{f4};

	t3.join();
	t4.join();

	return 0;
}
