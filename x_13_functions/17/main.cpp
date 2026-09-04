#include <iostream>
#include <string>
#include <cstdarg>
using namespace std;
enum class states {
	plain,
	pre_arg,
	arg
};

enum class arg_types {
	undefined,
	string,
	symb,
	decimal
};

void process_plain(states& state, char cur_letter) {
	if (cur_letter == '%') {
		state = states::pre_arg;
	}
	else {
		cerr << cur_letter;
	}
}

void process_pre_arg(states& state, arg_types& cur_type, char cur_letter) {
	switch(cur_letter) {
		case 's':
			cur_type = arg_types::string;
			state = states::arg;
			break;
		case 'c':
			cur_type = arg_types::symb;
			state = states::arg;
			break;
		case 'd':
			cur_type = arg_types::decimal;
			state = states::arg;
			break;
		default:
			state = states::plain;
	}
}

void process_arg(const arg_types cur_type, va_list pars, states& state) {
				switch(cur_type) {
					case arg_types::string: {
						char* s_arg = va_arg(pars, char*);
						cerr << s_arg;
						break;
					}
					case arg_types::symb: {
						int c_arg = va_arg(pars, int);
						cerr << static_cast<char>(c_arg);
						break;
					}
					case arg_types::decimal: {
						int d_arg = va_arg(pars, int);
						cerr << to_string(d_arg);
						break;
					}
				}

				state = states::plain;
}

void error(string txt ...) {
	va_list pars;
	va_start(pars, txt);
	states state {states::plain};
	arg_types cur_type {arg_types::undefined};
	for (int i = 0; i < txt.length(); ++i) {
		switch(state) {
			case states::plain:
				process_plain(state, txt[i]);	
				break;
			case states::pre_arg:
				process_pre_arg(state, cur_type, txt[i]);
				break;
			case states::arg:
				process_arg(cur_type, pars, state);
				break;
		}
	}

	va_end(pars);
	cerr << endl;
}

int main() {
	error("String val: %s, character value: %c, decimal value: %d!", "ququ", 'x', 7);
	return 0;
}
