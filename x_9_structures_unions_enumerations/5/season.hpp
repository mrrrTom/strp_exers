#include <iostream>
using namespace std;
#ifndef DVSEASON_HPP
#define DVSEASON_HPP

enum class season {
	spring = 0,
	summer = 1,
	autumn = 2,
	winter = 3
};


struct season_translator {
	private:
		static string _translation[4];
	public:
		static void set_translation(const string t[4]) {
			for (int i = 0; i < 4; i++) _translation[i] = t[i];
		}

		static string translate(int i) {
			return (_translation[i]);
		}

		static string translate(season& s) {
			int index = static_cast<int>(s);
			return _translation[index];
		}

		static season translate(string s) {
			for(int i = 0; i < 4; i++) {
				if(_translation[i] == s) return static_cast<season>(i);
			}

			throw runtime_error("wrong season string");
		}
};

string season_translator::_translation[4] =
{"spring", "summer", "autumn", "winter"};

season& operator++(season& s) {
	int i = static_cast<int>(s);
	++i;
	i = i % 4;
	s = static_cast<season>(i);
	return s;
}

season& operator--(season& s) {
	int i = static_cast<int>(s);
	--i;
	i = i % 4;
	s = static_cast<season>(i);
	return s;
}

istream& operator>>(istream& is, season& s) {
	string input;
	is >> input;
	s = season_translator::translate(input);
	return is;
}

ostream& operator<<(ostream& os, season& s) {
	cout << season_translator::translate(s);
	return os;
}
#endif
