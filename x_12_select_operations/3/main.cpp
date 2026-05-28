#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <map>
#include <string>
using namespace std;
using namespace chrono;
typedef long long unsigned int numeric;

template<typename T> numeric sum_w_for_ind_plain(vector<T>& v, int length) {
	numeric result{0};
	for (int i = 0; i < length; i++) result += v[i];
	return result;
}

template<typename T> numeric sum_w_for_ind_lambda(vector<T>& v, int l) {
	numeric result{0};
	auto f = [&result] (int a) -> void { result += a; };
	for (int i = 0; i < l; i++) f(i);
	return result;
}

struct S {
	numeric& sum;
	void operator()(int i) {
		sum += i;
	}
};

template<typename T> numeric sum_w_for_ind_funcobj(vector<T>& v, int l) {
	numeric result{0};
	S f {result};
	for (int i = 0; i < l; i++) f(i);
	return result;
}

template<typename T> numeric sum_w_for_ptr(vector<T>&v, int l) {
	long long unsigned int result{0};
	for (T* c = &v[0]; c != &v[l]; c++) result += *c;
	return result;
}

template<typename T> numeric sum_w_for_iter(vector<T>& v, int l) {
	long long unsigned int result{0};
	for (auto i = v.begin(); i != v.end(); i++) result += *i;
	return result;
}

template<typename T> numeric sum_w_range_for(vector<T>&v, int length) {
	long long unsigned int result{0};
	for (int i : v) result += i;
	return result;
}

template<typename T> numeric sum_w_foreach(vector<T>&v, int length) {
	numeric result{0};
	for_each(v.begin(), v.end(), [&result](T el) ->void { result += el; });
	return result;
}

template<typename T> numeric sum_w_while(vector<T>&v, int length) {
	numeric result{0};
	int i = 0;
	while(i < length) {
		result += v[i];
		i++;
	}

	return result;
}

template<typename T> using f_ = numeric(*)(vector<T>&, int);
template<typename T> int test(f_<T> f, vector<T>&v, int l) {
	auto start = high_resolution_clock::now();
	f(v, l);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	return duration.count();
}

template<typename T> void test(vector<T>&v, int l) {
	map<f_<T>, string> functions {
		{ sum_w_for_ind_plain, "sum with for with indices with plain code"},
		{ sum_w_for_ind_lambda, "sum with for with indices with lambda"},
		{ sum_w_for_ind_funcobj, "sum with for with indices with func obj"},
		{ sum_w_for_ptr, "sum with for with pointers"},
		{ sum_w_for_iter, "sum with for with iterators"},
		{ sum_w_range_for, "sum with range_for"},
		{ sum_w_foreach, "sum with foreach with lambda"},
		{ sum_w_while, "sum with while with indices with plain code"}
	};

	for (auto f : functions) {
		int time = test(f.first, v, l);
		cout << typeid(T).name() << " " << f.second << ": " << time << endl;
	}
}

int main() {
	vector<int> v (1000, 35);
	int l = v.size();
	test<int>(v, l);

	vector<double> vd(1000, 35.0);
	l = vd.size();
	test<double>(vd, l);
	return 0;
}
