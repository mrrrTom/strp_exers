$cat cpp_default_args
    Например, мы хотим, чтобы по умолчанию координаты были в точке (1, 1),
    тогда пишем:

```cpp
#include <iostream>
using namespace std;

struct coordinates {
    int x;
    int y;
    
    coordinates(int x_= 1, int y_ = 1) : x{x_}, y{y_} {}
    
    void print(void) {
        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
    }
};

int main() {
   coordinates cs;
   cs.print();
   return 0;
} 
```

    Интуитивно понятное объяснение, однако, тут есть место магии, дело в том,
    что в C++ умолчательное значение вычисляется не когда-нибудь там, а в
    момент вызова функции, что даёт нам возможность сделать следующее:

```cpp
    #include <iostream>
    using namespace std;

    struct coordinates {
        static int default_coordinate;
        int x;
        int y;

        coordinates(int x_= default_coordinate, int y_ = default_coordinate) : x{x_}, y{y_} {}

        void print(void) {
           cout << "x: " << x << endl;
           cout << "y: " << y << endl;
        }
    };

    int coordinates::default_coordinate = 1;
    int main() {
        coordinates cs;
        cs.print();

        coordinates::default_coordinate = 2;
        coordinates cs2;
        cs2.print();
        return 0;
    }

```

    Изменение умолчательного значения аргумента создаёт трудноотслеживаемые
    зависимости, такого лучше избегать [1].
    На самом деле, во многих случаях использования аргументов по умолчанию
    можно было бы избежать. Часто для разработчика это способ, не продумывая
    интерфейс, зафиксить конкретный сценарий. Стандарт на это смотрит менее
    негативно [2], а некоторые разработчики более негативно [3].

    [1] Б. Страуструп, Гл 12 Функции, 12.2.5 Аргументы по умолчанию
    [2] F.51. https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#rf-default-args
    [3] https://quuxplusone.github.io/blog/2020/04/18/default-function-arguments-are-the-devil/
$I
