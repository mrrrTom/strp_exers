$cat cpp_mutex
    При параллельном выполнении могут возникать неприятности. Например:
```cpp

    #include <thread>
    #include <iostream>
    using namespace std;

    void f1() {
		for (int i = 0; i < 100; i++)
		cout << "Hi everyone!! Hello from f1!" << endl;
	}

	void f2() {
		for (int i = 0; i < 100; i++)
		cout << "Hi, hi, hi, my friends!! Hello from f2!" << endl;
	}

    int main() 
    {
    	thread t1 {f1};
    	thread t2 {f2};
		t2.join();
    	t1.join();
		return 0;
    }
```

Ожидалось увидеть массу приветствий, самое страшное - в неопределённом порядке.
Однако на выходе появились пустые строчки. Или строчки типа "вывод1 + вывод2".
Дело в том, что обе функции осуществляют доступ к одному ресурсу - стандартный поток вывода в данном случае один.
И две функции пытаются записать в него что-то своё. Чтобы заставить функции дожидаться освобождения общего ресурса, а не хватать у другой, можно использовать специальный механизм синхронизации:
```cpp
    #include <thread>
    #include <iostream>
	#include <mutex>
	using namespace std;
	mutex m;

    void f1() {
		for (int i = 0; i < 100; i++)
		{
			unique_lock<mutex> lck {m};
			cout << "Hi everyone!! Hello from f1!" << endl;
		}
	}

	void f2() {
		for (int i = 0; i < 100; i++)
		{
			unique_lock<mutex> lck {m};
			cout << "Hi, hi, hi, my friends!! Hello from f2!" << endl;
		}
	}

    int main() 
    {
    	thread t1 {f1};
    	thread t2 {f2};
		t2.join();
    	t1.join();
		return 0;
    }
```
В данном случае в каждой итерации цикла захватывается семафор, а все остальные потоки, которые попытаются его захватить, будут ждать. Таким образом, мы получаем на каждой отдельной строчке запись одной или другой функции.
Если же мы захотим, чтобы сначала записала одна функция, затем другая, тогда семафор надо захватывать до цикла.
$I
