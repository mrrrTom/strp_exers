$cat task_params
    Стандартная библиотека C++ предоставляет средства реализации параллелизма. Например, задачи (активность, которую можно распараллелить) реализуются с помощью ```thread```.
    Задание передаётся потоку с помощью функционального объекта, описывающего требуемое действие. Например, если мы хотим, чтобы поток вывел что-то в стандартный вывод, то:
```cpp
    #include <thread>
    #include <iostream>
    using namespace std;

    struct F {
    	string o;
    	F(string output) : o{output} {}
    	void operator()() {
    		cout << o;
	    }
    };

    int main() 
    {
    	thread t {F{"hello"}};
    	t.join();
    	return 0;
    }
```

    Однако существует возможность передачи потоку просто функции следующим образом:
```cpp
    #include <thread>
    #include <iostream>
    using namespace std;

    void p(string output) {
    	cout << output;
    }

    int main() 
    {
    	thread t {p, "hello"};
    	t.join();
    	return 0;
    }
```
$I
