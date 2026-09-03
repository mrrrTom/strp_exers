#include <iostream>
#include <vector>
#include <map>
using namespace std;

enum class lexic_state {
	error,
	empty_line,
	pre_def,
	init,
	def,
	pre_comment,
	single_line_comment,
	multi_line_comment,
	pre_multi_line_comment_closure,
	var_can_be_used
};

enum class lexems : char {
	error,
	sharp = '#',
	w_space = ' ',
	n_line = '\n',
	tab = '\t',
	star = '*',
	slash = '/'
};

class macro_processor_fn {
	private:
		string const _define_key_word = "define";
		istream& _in;
		ostream& _out;
		lexic_state _state;
		vector<char> _cur_symbs;
		char _cur_s;
		void process_error() {
			cout << "Something bad has happend!" << endl;
		}

		void process_empty_line() {
			switch(_cur_s) {
				case static_cast<char>(lexems::sharp):
					_state = lexic_state::pre_def;
					cout << _cur_s;
					break;
				case static_cast<char>(lexems::slash):
					_state = lexic_state::pre_comment;
					cout << _cur_s;
					break;
				case static_cast<char>(lexems::w_space):
				case static_cast<char>(lexems::n_line):
				case static_cast<char>(lexems::tab):
					cout << _cur_s;
					break;
				default:
					_cur_symbs.push_back(_cur_s);
					_state = lexic_state::var_can_be_used;
					break;
			}
		}

		void process_pre_def() {
			cout << _cur_s;
			switch(_cur_s) {
				case static_cast<char>(lexems::w_space):
				case static_cast<char>(lexems::tab):
				{
					if (_cur_symbs.size() == 0) break;
					string cur_word {_cur_symbs.begin(), _cur_symbs.end()};
					if (cur_word == _define_key_word) {
						_state = lexic_state::init;
					}
					else {
						_state = lexic_state::error;
					}

					_cur_symbs.clear();
					break;
				}
				case static_cast<char>(lexems::n_line):
					_cur_symbs.clear();
					_state = lexic_state::empty_line;
					break;
				default:
					_cur_symbs.push_back(_cur_s);
					break;
			}
		}

		string _cur_init_word;
		bool has_wrong_word() {
			char first_symb = _cur_symbs[0];
			return ((first_symb < 'a') || (first_symb > 'z'));
		}

		void process_init() {
			cout << _cur_s;
			switch(_cur_s) {
				case static_cast<char>(lexems::w_space):
				case static_cast<char>(lexems::tab):
					if (_cur_symbs.size() != 0) {
						if (has_wrong_word()) {
							_cur_symbs.clear();
							_state = lexic_state::error;
						 }
						else {
							_cur_init_word = string {_cur_symbs.begin(), _cur_symbs.end()};
							_cur_symbs.clear();
							_state = lexic_state::def;
						}
					}

					break;
				case static_cast<char>(lexems::n_line):
					_cur_symbs.clear();
					_cur_init_word = "";
					_state = lexic_state::error;
					break;
				default:
					_cur_symbs.push_back(_cur_s);
					break;
			}
		}
		
		map<string, string> _defined_vars;
		void process_def() {
			cout << _cur_s;
			switch(_cur_s) {
				case static_cast<char>(lexems::n_line):
					if (_cur_symbs.size() != 0) {
						string new_val = string {_cur_symbs.begin(), _cur_symbs.end()};
						_defined_vars.insert({_cur_init_word, new_val});
						_cur_symbs.clear();
						_cur_init_word = "";
						_state = lexic_state::empty_line;
					}
					else {
						_cur_symbs.clear();
						_cur_init_word = "";
						_state = lexic_state::error;

					}

					break;
				default:
					_cur_symbs.push_back(_cur_s);
					break;
			}
		}

		void process_pre_comment() {
			cout << _cur_s;
			switch(_cur_s) {
				case static_cast<char>(lexems::slash):
					_state = lexic_state::single_line_comment;
					break;
				case static_cast<char>(lexems::star):
					_state = lexic_state::multi_line_comment;
					break;
				default:
					_state = lexic_state::error;
					break;
			}
		}

		void process_single_line_comment() {
			cout << _cur_s;
			switch(_cur_s) {
				case static_cast<char>(lexems::n_line):
					_state = lexic_state::empty_line;
					break;
				default:
					break;
			}
		}

		void process_multi_line_comment() {
			cout << _cur_s;
			switch(_cur_s) {
				case static_cast<char>(lexems::star):
					_state = lexic_state::pre_multi_line_comment_closure;
					break;
				default:
					break;
			}
		}

		void process_pre_multi_line_comment_closure() {
			cout << _cur_s;
			switch(_cur_s) {
				case static_cast<char>(lexems::slash):
					_state = lexic_state::var_can_be_used;
					break;
				case static_cast<char>(lexems::star):
					break;
				default:
					_state = lexic_state::multi_line_comment;
					break;
			}
		}

		void process_var_can_be_used() {
			switch(_cur_s) {
				case static_cast<char>(lexems::tab):
				case static_cast<char>(lexems::w_space): {
					if (_cur_symbs.size() != 0) {
						string cur_word = string {_cur_symbs.begin(), _cur_symbs.end()};
						if (_defined_vars.find(cur_word) != _defined_vars.end()) {
							cout << _defined_vars[cur_word];
							cout << static_cast<char>(lexems::w_space);
						}
						else {
							cout << cur_word << static_cast<char>(lexems::w_space);
						}

						_cur_symbs.clear();
						_state = lexic_state::var_can_be_used;
					}

					break;
				}
				case static_cast<char>(lexems::n_line): {
					if (_cur_symbs.size() != 0) {
						string cur_word = string {_cur_symbs.begin(), _cur_symbs.end()};
						if (_defined_vars.find(cur_word) != _defined_vars.end()) {
							cout << _defined_vars[cur_word];
							cout << static_cast<char>(lexems::w_space);
						}
						else {
							cout << cur_word << static_cast<char>(lexems::n_line);
						}
_cur_symbs.clear();
						_state = lexic_state::empty_line;
					}

					break;
				}
				default: {
					if (_cur_symbs.size() != 0) {
						string cur_word = string {_cur_symbs.begin(), _cur_symbs.end()};
						if (_defined_vars.find(cur_word) != _defined_vars.end()) {
							cout << _defined_vars[cur_word];
							_cur_symbs.clear();
						}
					}
					
					_cur_symbs.push_back(_cur_s);
					_state = lexic_state::var_can_be_used;
					break;
				}
			}
		}

		void process(char cur_s) {
			_cur_s = cur_s;
			switch(_state) {
				case lexic_state::error:
					process_error();
					return;
				case lexic_state::empty_line:
					process_empty_line();
					break;
				case lexic_state::pre_def:
					process_pre_def();
					break;
				case lexic_state::init:
					process_init();
					break;
				case lexic_state::def:
					process_def();
					break;
				case lexic_state::pre_comment:
					process_pre_comment();
					break;
				case lexic_state::single_line_comment:
					process_single_line_comment();
					break;
				case lexic_state::multi_line_comment:
					process_multi_line_comment();
					break;
				case lexic_state::pre_multi_line_comment_closure:
					process_pre_multi_line_comment_closure();
					break;
				case lexic_state::var_can_be_used:
					process_var_can_be_used();
					break;
			}
		}
	public:
		macro_processor_fn(istream& in_, ostream& out_) : _in{in_}, _out{out_}, _state{lexic_state::empty_line} {}

		void operator()() {
			char cur_s;
			while(_in.get(cur_s)) {
				process(cur_s);
			}
		}
};

int main (int argc, char *argv[]) {
	macro_processor_fn process_macroses(cin, cout);
	process_macroses();
	return 0;
}

