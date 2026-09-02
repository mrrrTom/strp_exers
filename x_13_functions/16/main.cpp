#include <iostream>
#include <vector>
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
					break;
				case static_cast<char>(lexems::slash):
					_state = lexic_state::pre_comment;
					break;
				case static_cast<char>(lexems::w_space):
				case static_cast<char>(lexems::n_line):
				case static_cast<char>(lexems::tab):
					break;
				default:
					_state = lexic_state::var_can_be_used;
					break;
			}
		}

		void process_pre_def() {
			switch(_cur_s) {
				case static_cast<char>(lexems::w_space):
				case static_cast<char>(lexems::tab):
				{
					if (_cur_symbs.size() == 0) break;
					string cur_word {_cur_symbs.begin(), _cur_symbs.end()};
					if (cur_word == _define_key_word) _state = lexic_state::init;
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

		void process_init() {
			switch(_cur_s) {
				case static_cast<char>(lexems::w_space):
				case static_cast<char>(lexems::tab
			}
		}

		void process_def() {
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

