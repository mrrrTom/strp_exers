#include <iostream>
#include <map>
#include <string>
#include <dv_sorted_list.hpp>

using namespace std;
using namespace dv_sorted_list;

sorted_list* _values;
map<string, sorted_list*> _named_values;

void print_named() {
	for (auto pair : _named_values) {
		cout << pair.first << " sum: " << pair.second -> sum()
			<< " mean: " << pair.second -> mean() 
			<< " median: " << pair.second -> median() << endl;
	}
}

void print_all() {
	cout << "Total sum: " << _values -> sum()
		<< " total mean: " << _values -> mean()
		<< " total median: " << _values -> median() << endl;
}

void fill_storage() {
	string key;
	double value;
	while (cin >> key && cin >> value) {
		_values -> insert(value);
		if (_named_values.find(key) == _named_values.end()) {
			sorted_list* lst = new sorted_list();
			lst -> insert(value);
			_named_values[key] = lst;
		}
		else {
			_named_values[key] -> insert(value);
		}
	}
}

void delete_named() {
	for (auto pair : _named_values)
		delete(pair.second);
}

int main() {
	_values = new sorted_list();
	fill_storage();
	print_named();
	print_all();
	delete_named();	
	delete(_values);
	return 0;
}
