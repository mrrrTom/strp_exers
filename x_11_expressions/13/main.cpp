#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

enum class Kind : char {
	name, 
	number, 
	end, // =
	endl, // \n
	assign, // :=
	plus = '+',
	minus = '-', 
	mul = '*', 
	div = '/', 
	print = ';',
	lp = '(', 
	rp = ')'
};

struct Token{
	Kind kind;
	string raw_value;
	string string_value;
	double number_value;
	Token(Kind kind_, char raw_) : kind{kind_}, raw_value{raw_} {}
	Token(Kind kind_, string raw_) : kind{kind_}, raw_value{raw_} {}
	Token(Kind kind_, string raw_, string val_) : kind{kind_}, raw_value{raw_},
		string_value{val_} {}
	Token(Kind kind_, string raw_, double num_) : kind{kind_}, raw_value{raw_},
	number_value{num_} {}
};

// bad idea to make it global..
int errors_count = 0;
int line_count = 1;

double error(const string& s) {
	errors_count++;
	cerr << "error: " << s << " at line: " << line_count << endl;
	return 1;
}

class Token_stream {
	public:
		Token_stream(istream& s) : ip{&s}, owns{false} { }
		Token_stream(istream* p) : ip{p}, owns{true} { }
		~Token_stream() { close(); }
		Token get() {
			char ch;
			do {
				if (!ip -> get(ch)) return ct = Token(Kind::end, ch);
			} while (ch != '\n' && isspace(ch));
			
			switch (ch) {
				case '\n':
					line_count++;
					return ct = Token(Kind::endl, ch); 
				case '=':
					return ct = Token(Kind::end, ch);
				case ':':
					ip -> get(ch);
					if (ch != '=') error("expected '='");
					return ct = Token(Kind::assign, ":=");
				case '*':
				case '/':
				case '+':
				case '-':
				case '(':
				case ')':
					return ct = Token(static_cast<Kind>(ch), ch);
				case '0': case '1': case '2': case '3': case '4': case '5':
				case '6': case '7': case '8': case '9': case '.':
					ip -> putback(ch);
					double num_val;
					*ip >> num_val;
					return ct = Token(Kind::number,
							to_string(num_val),
							num_val);
				default:
					if (isalpha(ch)) {
						ip -> putback(ch);
						string str_val;
						*ip >> str_val;
						return ct = Token(Kind::name, str_val, str_val);
					}

					error("bad token");
					return ct = Token(Kind::end, ch);
			}
		}
	
		const Token& current() { return ct; }
		
		void set_input(istream& s) { close(); ip = &s; owns = false; }
		void set_input(istream* p) { close(); ip = p; owns = true; }
	private:
		void close() { if (owns) delete ip; }

		istream* ip;
		bool owns;
		Token ct = Token(Kind::end, '\0');
};

map<string, string> names_replacement;

class Calculator {
	public:
		double expr (bool);
		double prim (bool);
		double term (bool);
		void calculate(void);
		Calculator(Token_stream ts, ostream& os) : _ts{ts}, _os{os} {};
	private:
		// bad idea, that calculator knows smth about streams
		Token_stream _ts;
		ostream& _os;
};

double Calculator::prim (bool get) {
	if (get) _ts.get();

	switch (_ts.current().kind) {
		case Kind::number:
			{
				double v = _ts.current().number_value;
				_ts.get();
				return v;
			}
		case Kind::name:
			{
				if (_ts.get().kind == Kind::assign) {
					string val = "";
					while (_ts.get().kind != Kind::endl) {
						val += _ts.current().raw_value;
					}

					names_replacement[_ts.current().string_value] = val;
					return 0;
				}
				else {
					// dirty hack, but cool
					stringstream ss
							{names_replacement[_ts.current().string_value]};
					stringstream os;
					Calculator func_calc(ss, os);

					// and it is not operations, it is lambda function))
					func_calc.calculate();
					double v = stod(os.str());
					return v;
				}
			}
		case Kind::minus:
			return -prim(true);
		case Kind::lp:
			{
				auto e = expr(true);
				if (_ts.current().kind != Kind::rp) return error("')' expected");
				_ts.get();
				return e;
			}
		default:
			return error("primary expected");
	}
}
double Calculator::term(bool get) {
	double left = prim(get);
	for(;;) {
		switch (_ts.current().kind) {
			case Kind::mul:
				left *= prim(true);
				break;
			case Kind::div:
				if (auto d = prim(true)) {
					left /= d;
					break;
				}

				return error("divide by 0");
			default:
				return left;
		}
	}
}
double Calculator::expr(bool get) {
	double left = term(get);
	for(;;) {
		switch (_ts.current().kind) {
			case Kind::plus:
				left += term(true);
				break;
			case Kind::minus:
				left -= term(true);
				break;
			default:
				return left;
		}
	}
}

void Calculator::calculate() {
	for (;;) {
		_ts.get();
		if (_ts.current().kind == Kind::end) break;
		if (_ts.current().kind == Kind::endl) continue;
		_os << expr(false) << endl;
	}
}

int main(void) {
	names_replacement["pi"] = 3.1415926;
	names_replacement["e"] = 2.71828;
	Token_stream ts{cin};
	Calculator calc(ts, cout);
	calc.calculate();
	return errors_count;
}
