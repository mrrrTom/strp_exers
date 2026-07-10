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
