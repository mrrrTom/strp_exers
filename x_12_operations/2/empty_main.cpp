#include <iostream>
#include <thread>
using namespace std;

void run(void) {
	unsigned long int i = 0;
	try {
		while(true) {
			int* k = new int[100];
			i++;
		}
	}
	catch(const bad_alloc&) {
		cout << "shunk size: " << sizeof(int[100]) << endl;
		cout << "shunks allocated empty: " << i << endl;
	}
	catch(...) {
		cout << "smth thrown" << endl;
	}
}

int main() {
	thread t(run);
	t.join();
	return 0;
}
