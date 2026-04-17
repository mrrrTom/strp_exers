#ifndef DV_COMMENT_ERASER_HPP
#define DV_COMMENT_ERASER_HPP
#include <iterator>
#include <iostream>
using namespace std;

namespace dv_comment_eraser {
	enum class state {
		code,
		presumably_comment,
		ml_comment,
		sl_comment,
		quote,
		presumably_stop_ml_comment,
		presumably_ml_comment_error,
		presumably_sl_comment_error,
		comment_error,
		finish
	};

	struct state_machine {
		private:
			state _cur_state;
		public:
			state_machine();
			state get_state();
			void change_state(char symb);
			void finish();
	};

	struct comment_eraser {
		private:
			istreambuf_iterator<char> _cursor;
			istreambuf_iterator<char> _end;
			state_machine _sm;
			ostream& _os;
			void (*get_print(state s))(char c, ostream& os);
		public:
			comment_eraser(istream& is, ostream& os);
			void print_comment_free();
	};
	
	comment_eraser::comment_eraser(istream& is, ostream& os) : _sm(), 
													_cursor{is},
													_end{},
													_os{os}
	{};
	
	// + quote_print
	// + sl_comment_print
	// + presumably_sl_comment_error_print
	void simple_print(char c, ostream& os) { os << c; };
	
	void empty_print(char c, ostream& os) {};

	void code_print(char c, ostream& os) {
		if (c == '/') return;
		os << c;
	}

	void presumably_comment(char c, ostream& os) {
		if (c == '/' || c == '"' || c == '*') return;
		os << '/';
		os << c;
	}


	void (*comment_eraser::get_print(state s))(char c, ostream&) {
		return &simple_print;
	}

	void comment_eraser::print_comment_free() {
		while(!_cursor.equal(_end)) {
			state st = _sm.get_state();
			auto st_print = get_print(st);
			st_print(*_cursor, _os);
			_sm.change_state(*_cursor);
			_cursor++;
		}
		
		_sm.finish();
	}

	state_machine::state_machine() : _cur_state{state::code} {};

	state state_machine::get_state() {
		return _cur_state;
	}

	void state_machine::finish() {
		_cur_state = state::finish;
	}
	
	void state_machine::change_state(char symb) {
		switch(_cur_state) {
			case state::code:
				if(symb == '"') { 
					_cur_state = state::quote; 
				}
				else if (symb == '/') { 
					_cur_state = state::presumably_comment; 
				}
				break;
			case state::presumably_comment:
				if(symb == '"') {
					_cur_state = state::quote;
				}
				else if (symb == '*') {
					_cur_state = state::ml_comment;
				}
				else if (symb == '/') {
					_cur_state = state::sl_comment;
				}
				else {
					_cur_state = state::code;
				}
				break;
			case state::ml_comment:
				if(symb == '*') {
					_cur_state = state::presumably_stop_ml_comment;
				}
				else if (symb == '/') {
					_cur_state = state::presumably_ml_comment_error;
				}
				break;
			case state::sl_comment:
				if(symb == '/') {
					_cur_state = state::presumably_sl_comment_error;
				}
				else if(symb == '\n') {
					_cur_state = state::code;
				}
				break;
			case state::quote:
				if(symb == '"') {
					_cur_state = state::code;
				}
				break;
			case state::presumably_stop_ml_comment:
				if(symb == '"') {
					_cur_state = state::quote;
				}
				else if (symb == '/') {
					_cur_state = state::code;
				}
				else {
					_cur_state = state::ml_comment;
				}
				break;
			case state::presumably_ml_comment_error:
				if(symb == '/' || symb == '*') {
					_cur_state = state::comment_error;
				}
				else {
					_cur_state = state::ml_comment;
				}
				break;
			case state::presumably_sl_comment_error:
				if(symb == '/' || symb == '*') {
					_cur_state = state::comment_error;
				}
				else {
					_cur_state = state::sl_comment;
				}
				break;
			case state::comment_error:
				break;
			case state::finish:
				break;
		}
	}
}
#endif
