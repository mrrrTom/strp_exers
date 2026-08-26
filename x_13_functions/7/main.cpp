#include <iostream>
#include <assert.h>
#include <algorithm>
using namespace std;
struct element {
	int size;
	char* val_ptr;
	element(int size_, char* val_ptr_) : size{size_}, val_ptr{val_ptr_} {}
	element(const element& el) {
		size = el.size;
		char* new_val_ptr = new char[size];
		this->val_ptr = new_val_ptr;
		char* r_ptr = el.val_ptr;
		for (int i = 0; i < size; ++i) {
			*new_val_ptr = *r_ptr;
			new_val_ptr++;
			r_ptr++;
		}
	}
	element(element&& el) {
		size = el.size;
		char* new_val_ptr = new char[size];
		this->val_ptr = new_val_ptr;
		char* r_ptr = el.val_ptr;
		for (int i = 0; i < size; ++i) {
			*new_val_ptr = *r_ptr;
			new_val_ptr++;
			r_ptr++;
		}
	}
	element& operator=(const element& right) {
		if (this -> size != right.size) throw runtime_error("bad things");
		char* left_ptr = this -> val_ptr;
		char* right_ptr = right.val_ptr;
		for (int i = 0; i < size; ++i) {
			*left_ptr = *right_ptr;
			left_ptr++;
			right_ptr++;
		}

	return *this;
	}

	bool operator==(element right) {
		if (this -> size != right.size) throw runtime_error("bad things");
		char* left_ptr = this -> val_ptr;
		char* right_ptr = right.val_ptr;
		for (int i = 0; i < size; ++i) {
			if (*left_ptr != *right_ptr) return false;
			left_ptr++;
			right_ptr++;
		}

		return true;
	}

	element operator++() {
		char* new_ptr = val_ptr;
		for (int i = 0; i < size; ++i) {
			new_ptr++;
		}

		this->val_ptr = new_ptr;
		return *this;
	}

	element operator--() {
		char* new_ptr = val_ptr;
		for (int i = 0; i < size; ++i) {
			new_ptr--;
		}

		this->val_ptr = new_ptr;
		return *this;
	}
	~element() {}
};

class element_iter {
	private:
		element* _cur;
		int _size;
	public:
		using value_type = element;
		using difference_type = int;
		using pointer = element*;
		using reference = element&;
		using iterator_category = random_access_iterator_tag;
		element_iter (char* ptr, int size) {
			_cur = new element{size, ptr};
			_size = size;
		}

		element_iter (element_iter& el) {
			element* new_el = new element(el._size, el._cur->val_ptr);
			this->_size = el._size;
			_cur = new_el;
		}

		int operator-(element_iter right) {
			return -((right._cur->val_ptr - this->_cur->val_ptr) / _size);
		}
		bool operator!=(element_iter right) {
			return ((_cur->val_ptr) != (right._cur->val_ptr));
		}
		element& operator*() {
			return *_cur;
		}
		element_iter& operator--(){
			char* new_ptr = this->_cur->val_ptr;
			for (int i = 0; i < _size; ++i) {
				new_ptr--;
			}

			this->_cur->val_ptr = new_ptr;
			return *this;
		}
		element_iter operator+(int add) {
			element_iter el_i{_cur->val_ptr, _cur->size};
			for (int i = 0; i < add; ++i) {
				++el_i;
			}

			return el_i;
		}
		element_iter operator-(int minus) {
			element_iter el_i{_cur->val_ptr, _cur->size};
			for (int i = 0; i < minus; ++i) {
				--el_i;
			}

			return el_i;

		}
		element_iter& operator++() {
			char* new_ptr = this->_cur->val_ptr;
			for (int i = 0; i < _size; ++i) {
				new_ptr++;
			}

			this->_cur->val_ptr = new_ptr;
			return *this;
		}
		bool operator==(element_iter right) {
			return ((this->_cur->val_ptr) == (right._cur->val_ptr));
		}
		bool operator<(element_iter right) {
			return (this->_cur->val_ptr < right._cur->val_ptr);
		}
		bool operator>(element_iter right) {
			return (this->_cur->val_ptr > right._cur->val_ptr);
		}
		element_iter& operator=(element_iter el) {
			element* new_el = new element(el._size, el._cur->val_ptr);
			new_el->size = el._size;
			_cur = new_el;
			return *this;
		}
		~element_iter() {
		}
};

template <typename T>
class element_comparator {
public:
	int operator() (element& l, element& r) {
		T l_val = *(reinterpret_cast<const T*>(l.val_ptr));
		T r_val = *(reinterpret_cast<const T*>(r.val_ptr));
		bool res = (l_val < r_val);
		return res;
	}
};

template <typename T> void ssort_new(void* base, size_t n, size_t sz, element_comparator<T> cmp) {
	element_iter start{reinterpret_cast<char*>(base), static_cast<int>(sz)};
	char* ptr = reinterpret_cast<char*>(base);
	ptr = ptr + n * sz;
	element_iter end {ptr, static_cast<int>(sz)};
	sort(start, end, cmp);
}

void print(int arr[5]) {
	for (int i = 0; i < 5; ++i) {
		cout << arr[i] << " ";
	}

	cout << endl;
}
int main (int argc, char *argv[]) {
	int arr[5] { 6, 3, 0, 2, 1};
	print(arr);
	element_comparator<int> el_c;
	ssort_new(&arr[0], 5, 4, el_c);
	print(arr);
	return 0;
}
