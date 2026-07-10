$cat cpp_safe_union
    Есть такая штука в плюсах, которая называется Union. Относится оно скорее к
    тёмным искусствам, к которым надо прибегать только если у тебя прямые руки.
    Например, вот что про объединения пишет г-н Страуструп[1]:
    "Я считаю, что объединения на практике применяются неоправданно часто;
    по-возможности их следует избегать".
    Думаю, что опасения автора связаны с богатым разнообразием ошибок, которых
    можно наделать, используя объединения. Например, они позволяют делать "каст"
    без использования приведения в явном виде. Но опасность в том, что для того,
    чтобы union сработал в таком сценарии, типы в своей реализации должно
    одинаковым образом располагать биты в памяти, что, строго говоря, не
    гарантировано стандартом и так далее.
    Но есть и сценарии, где использование объединений будет оправдано, а для
    избежания ошибок можно использовать языковые средства. Например:
    мы пишем приложение для обработки большого количества денежных переводов.
    Рассмотрим самый простой сценарий: прилетает набор транзакций, надо его
    как-то обработать, загрузив в память. Добавим все транзакции в контейнер
    и выведем их количество:

```cpp
    #include <iostream>
    #include <string>
    #include <vector>
    using namespace std;
    struct transaction {
    	int user_id;
    	long value;
    };

    istream& operator>>(istream& in, transaction& trans) {
    	return (in >> trans.user_id >> trans.value);
    }

    int main() {
    	int result = 0;
    	vector<transaction> chunk;
    	transaction temp;
    	while(cin >> temp) {
    		chunk.push_back(temp);
    	}
	
    	cout << chunk.size();
	    return 0;
    }
```
    У этой реализации максимальная алоцированная память в куче составляет около
    16 Mb при обработке 9 млн записей транзакций (valgring - massif).
    Проблема данной реализации в том, что большинство транзакций укладывается
    в short (это допущение в рамках этого примера, но допущение соотносящееся
    с действительностью - очень большие транзакции, которые не будут влезать
    в, например, short или int, встречаются намного реже остальных).
    Таким образом, большое количество памяти у нас пустует, вот бы заменить
    long -> short и пусть дельту на что-то полезное. Для этого создадим
    структуру, соответствующую транзакции с небольшой суммой, которая
    влезает в short и структуру, соответствующую большой транзакции, которая
    помещается только в long и больше. А в нашей изначальной транзакции будем
    содержать либо непосредственно маленькую транзакцию, либо ссылку на большую.

```cpp
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <climits>
    #include <unordered_set>
    using namespace std;

    // sizeof() == 16 (+4 - alignment)
    struct big_transaction {
    	int user_id;
    	long value;

	    big_transaction(int user_id, long value) {
	    	this -> user_id = user_id;
	    	this -> value = value;
	    }
    };

    // sizeof() = 8
    struct little_transaction {
    	int user_id;
    	short value;
	
    	little_transaction() {}
    	little_transaction(int user_id, short value) {
	    	this -> user_id = user_id;
		    this -> value = value;
	    }
    };

    // чтобы не хранить флаг в struct transaction, потому что alignment
    // в таком случае сведёт на нет оптимизацию по памяти, доведя размер
    // transaction до 16
    unordered_set<big_transaction*> ext_transactions;

    // sizeof() = 8
    struct transaction {
    	union {
    		little_transaction std_transaction;
    		big_transaction* ext_transaction;
    	};

	    transaction() : std_transaction() {}

    	void set(int user_id, long value) {
             // внешние ссылки на большие транзакции позволяют нам быстро
             // оценить количество таких транзакций, чтобы оценить 
             // эффективность оптимизации
    		this -> ext_transaction = new big_transaction(user_id, value);
    		ext_transactions.insert(this -> ext_transaction);
	    }

	    void set(int user_id, short value) {
	    	this -> std_transaction.user_id = user_id;
	    	this -> std_transaction.value = value;
	    }

	    bool is_ext() {
	    	return (ext_transactions.find(this -> ext_transaction) !=
	    			ext_transactions.end());
    	}

    	~transaction() {
    		if(this -> is_ext()) {
    			ext_transactions.erase(this -> ext_transaction);
    			delete(this -> ext_transaction);
    		}
    	}
    };

    istream& operator >> (istream& in, transaction& trans) {
    	int user_id;
    	in >> user_id;
    	long b_value;
    	in >> b_value;
    	if (b_value <= SHRT_MAX) {
    		trans.set(user_id, static_cast<short>(b_value));
    	}
    	else {
    		trans.set(user_id, b_value);
    	}

	    return in;
    }

    int main() {
    	cout << sizeof(transaction) << endl;
    	int result = 0;
    	ifstream fs;
    	fs.open("./input");
    	vector<transaction> chunk;
    	transaction temp;
    	while(fs >> temp) {
    		chunk.push_back(temp);
	    }

	    cout << "big transactions: " << ext_transactions.size() << endl;
	    cout << "chunk size: " << chunk.size() << endl;
	    return 0;
    }
```
    
    Оба варианта я проверял на одних и тех же данных - 1 млн транзакций,
    из них 30 - большие (не помещаются в short). Для второго варианта
    максимальная алоцированная память в куче - около 8 Mb, то есть в два раза
    сократился объём используемой памяти. В данной реализации выигрыш случился
    как раз за счёт использования union, если бы такого механизма не было, то
    в структуре transaction нужно бы было резервировать память под маленькую
    транзакцию и под ссылку на большую, что, учитывая выравнивание, дало бы
    sizeof = 16, что свело бы на нет данную оптимизацию.
$I
