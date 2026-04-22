#include <iostream>
#include <map>
#include <string>
using namespace std;

map<string, double> _storage;
map<string, int> _stored_count;
double _total_count;
double _total_summ;

void print_every() {
	for (auto pair : _storage) {
		cout << pair.first << " sum: " << pair.second
			<< " mean: " << (pair.second / _stored_count[pair.first]) << endl;
	}
}

void print_agregate() {
	cout << "sum total: " << _total_summ << " mean: " 
	<< (_total_summ / _total_count) << endl;
}

void fill_storage() {
	string key;
	double value;
	while (cin >> key && cin >> value) {
		_total_count++;
		_total_summ += value;
		if (_storage.find(key) == _storage.end()) {
			_storage[key] = value;
			_stored_count[key] = 1;
		}
		else {
			_storage[key] += value;
			_stored_count[key]++;
		}
	}
}

int main() {
	fill_storage();
	print_every();
	print_agregate();
	return 0;
}
