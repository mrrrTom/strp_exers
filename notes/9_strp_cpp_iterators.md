$cat cpp_iterators
    Контейнеры стандартной библиотеки предоставляют методы begin() и end(), которые можно использовать, например, в циклах следующим образом:
```cpp
    #include <iostream>
    #include <vector>

    int main() {
        vector<int> testVector(5, 1);
        for (auto element = testVector.begin(), elemenent != testVector.end(), element++) {
            std::cout << element;
            }

        return 0;
    }
```

    Чтобы понять, что такое итератор, давайте посмотрим на реализацию метода `begin()` в стандартной библиотеке реализации GCC (gcc-11.2.0/libstdc++).
```cpp
    iterator
    begin() _GLIBCXX_NOEXCEPT
    { return iterator(this->_M_impl._M_start); }
```
    Пока не сильно помогло - мы узнали, что возвращается класс `iterator` с каким-то началом. Выше можно найти следующее определение: 
```cpp
    typedef __gnu_cxx::__normal_iterator<pointer, vector> iterator;
```
    Находим конструктор 
```cpp
    __normal_iterator(const _Iterator& __i) : _M_curent(__i) {}
```
    И для `_M_current` находим следующее:
```cpp
    template<typename _Iterator, typename _Container>
    class __normal_iterator
    {
    protected:
        _Iterator _M_current;
    //...
```
    В нашем случае надо выяснить, что такое `_M_impl._M_start`. Оно берётся из определения в файле класса вектора:
```cpp
    public:
    _Vector_impl _M_impl;
```
    В классе `_Vector_impl_data`, являющимся классом родителем для класса `_Vector_impl`, находим определение:
```cpp
    pointer _M_start;
``` 
Класс pointer - в данном случае это просто указатель, что подтверждается следующим блоком:
```cpp
    protected:
        void
        _M_create_storage(size_t __n)
        {
            this -> _M_impl._M_start = this -> _M_allocate(__n);
            ///...
        }
```
    Таким образом, итератор для класса `Vector` - это просто указатель, причем итератор, который возвращается методом `begin()` - это указатель на первый элемент. Тогда становится понятна семантика обращения с итератором, например операции `++` - это арифметика указателей. А, как мы знаем, указатели можно сравнивать, что так же использовалось в цикле выше.

    Итераторы используются не только при работе с контейнерами, но и с потоками, и с алгоритмами, Б. Страуструп приводит [1] такой пример:
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>

using namespace std;

int main() {
	string from, to;
	cin >> from >> to;

	ifstream is {from};
	istream_iterator<string> ii {is};
	istream_iterator<string> eos {};

	ofstream os{to};
	ostream_iterator<string> oo {os, "\n"};

	vector<string> b{ii, eos};
	sort(b.begin(), b.end());
	
	unique_copy(b.begin(), b.end(), oo);

	return !is.eof()|| !os;
}
```

[1] Б. Страуструп, "Язык программирования C++", четвёртое издание, Москва 2023, издательство БИНОМ, 4.5.3.
$I
