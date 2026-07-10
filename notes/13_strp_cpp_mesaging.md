$cat threads_messaging
    С помощью стандартных механизмов синхронизации можно обеспечить коммуникацию между потоками:

```cpp
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
#include <thread>

using namespace std;

mutex m;
condition_variable cond;

struct message {
	string header;
	string body;
};

queue<message> q;

void consumer() {
	while(true) {
		unique_lock<mutex> lck {m};
		cond.wait(lck);
		auto msg  = q.front();
		q.pop();
		lck.unlock();
		cout << "header: " << msg.header << " body: " << msg.body << endl;
	}
}

void producer() {
	while(true) {
		message msg;
		msg.header = "test";
		msg.body = "Hello. friend";
		unique_lock<mutex> lck{m};
		q.push(msg);
		cond.notify_one();
	}
}

int main() 
{
	thread t1 {consumer};
	thread t2 {producer};
	t1.join();
	t2.join();

	return 0;
}
```
$I
