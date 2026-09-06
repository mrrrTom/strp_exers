#include <iostream>
#include <chrono>
using namespace std;

struct Date {
	private:
		static constexpr short _months_l [13] = { -1, // undefined
					   31, // january
					   28, // february
					   31, // march
					   30, // april
					   31, // may
					   30, // june
					   31, // july
				       31, // august
					   30, // september
					   31, // october
					   30, // november
					   31  // december
					};
		short _y;
		short _m;
		short _d;
	public:
		void set_year(short);
		short get_year() const;
		void set_month(short);
		short get_month() const;
		void set_day(short);
		short get_day() const;
		static string get_supported_formats();
		void add_year(int);
		void add_month(int);
		void add_day(int);
		int get_w_day();
		Date get_n_monday_day();
		Date() {};
		Date(short year, short month, short day) {
			set_year(year);
			set_month(month);
			set_day(day);
		}
};

ostream& operator << (ostream&, Date&);
istream& operator >> (istream&, Date&);

int main (int argc, char *argv[]) { cout << "insert date in format: YYYY MM DD: ";
	short year, month, day;
	cin >> year >> month >> day;
	Date n_date{year, month, day};
	cout << "inserted date: " << n_date << endl;
	n_date.add_year(1);
	n_date.add_month(2);
	n_date.add_day(3);
	cout << "date after adding 1 year 2 month 3 days: " << n_date << endl;
	return 0;
}

Date Date::get_n_monday_day() {
	while (this->get_w_day() != 1) {
		this->add_day(1);
	}

	return *this;
}
int Date::get_w_day() {
	return 1; // sometimes it will give the right answer
}


void Date::add_year(int y) {
	_y += y;
}

void Date::add_month(int m) {
	_m += m;
}

void Date::add_day(int d) {
	_d += d;
}

string Date::get_supported_formats() {
	return "dd mm yyyy";
}

void Date::set_year(short y) {
	if(y < 0 || y > 30000) throw("Wrong input");
	_y = y;
}

short Date::get_year() const {
	if(!_y) throw("Year not set");
	return _y;
}

void Date::set_month(short m) {
	if(m < 0 || m > 12) throw("Wrong input");
	_m = m;
}

short Date::get_month() const {
	if(!_m) throw("Month not set");
	return _m;
}

void Date::set_day(short d) {
	short max_day = _months_l[this -> get_month()];
	if (d < 1 || d > max_day) throw("Wrong input");
	_d = d;
}

short Date::get_day() const {
	if(!_d) throw("Day not set");
	return _d;
}

ostream& operator << (ostream& os, Date& dt) {
	os << dt.get_day() << "." << dt.get_month() << "." << dt.get_year() << endl;
	return os;
}

istream& operator >> (istream& is, Date& dt) {
	short year;
	short month;
	short day;
	is >> day >> month >> year;
	dt.set_year(year);
	dt.set_month(month);
	dt.set_day(day);
	return is;
}
