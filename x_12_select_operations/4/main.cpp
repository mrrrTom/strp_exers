#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Shape {
	virtual double GetArea() = 0;
	virtual void inc(void) = 0;
};

struct circle : public Shape {
	private:
		int _radius = 0;
	public:
		circle() = delete;
		circle(int r) : _radius{r} {}
		void inc() override { _radius++; }
		void set_radius(int r) { _radius = r; }
		double GetArea() override {
			return (_radius * _radius * M_PI);
		}
};

struct square : public Shape {
	private:
		int _a = 0;
	public:
		square() = delete;
		square(int a) : _a{a} {}
		void set_a(int a) { _a = a; }
		void inc(void) override { _a++; }
		double GetArea() override {
			return (_a * _a);
		}
};

#ifdef USING
using f_ = void (*) (Shape*);
void apply(vector<Shape*> v, f_ f) {
	for_each(v.begin(), v.end(), f);
}
#endif
#ifdef TEMPLATE
template <typename T>
void apply(vector<Shape*> v, T f) {
	for_each(v.begin(), v.end(), f);
}
#endif
#ifdef AUTO
void apply(vector<Shape*> v, auto f) {
	for_each(v.begin(), v.end(), f);
}
#endif

double _summ_area = 0;
void add_summ(Shape* s) {
	_summ_area += s -> GetArea();
}

void print_type(Shape* s) {
	 const type_info& ti = typeid(s);
	 cout << ti.name() << endl;
}

struct mutabor {
	static void operator() (Shape* s) {
		circle* c = dynamic_cast<circle*>(s);
		square* sq = dynamic_cast<square*>(s);
		
		int new_val = rand();
		if (c != nullptr) { 
			cout << "circle mutation" << endl;
			c -> set_radius(new_val);
			return;
		}

		if (sq != nullptr) {
			cout << "square mutation" << endl;
			sq -> set_a(new_val);
			return;
		}

		cout << "empty mutation" << endl;
	}
};

#ifdef TEMPLATE

template<typename R, typename T>
R process (T func);

using f_ = void (*) (Shape*);
template<>
int process<int,f_>(f_ func) {
#else
int process() {
#endif
	vector<Shape*> shapes;
	square s1{1};
	square s2{2};
	square s3{3};
	square s4{4};
	circle c1{1};
	circle c2{2};
	circle c3{3};
	circle c4{4};
	shapes.push_back(&s1);
	shapes.push_back(&s2);
	shapes.push_back(&s3);
	shapes.push_back(&s4);
	shapes.push_back(&c1);
	shapes.push_back(&c2);
	shapes.push_back(&c3);
	shapes.push_back(&c4);
#ifdef USING
	f_ f = [](Shape* s) -> void { cout << s -> GetArea() << endl; };

#endif
#ifdef TEMPLATE
	f_ f = func;
#endif
#ifdef AUTO
	auto f = [](Shape* s) -> void { cout << s -> GetArea() << endl; };

#endif
	apply(shapes, f);

	apply(shapes, add_summ);
	cout << "calculated summ: " << _summ_area << endl;

	apply(shapes, print_type);

	apply(shapes, [](Shape* s){ s -> inc(); });

	apply(shapes, [](Shape* s){ cout << s -> GetArea() << endl; });
	
	mutabor m;
	apply(shapes, &mutabor::operator());
	
	apply(shapes, [](Shape* s){ cout << s -> GetArea() << endl; });
	
	return 0;
}

int main() {
#ifdef TEMPLATE
	auto f = [](Shape* s) -> void { cout << s -> GetArea() << endl; };
	int i = process<int, f_>(f);
#else
	process();
#endif
	return 0;
}
