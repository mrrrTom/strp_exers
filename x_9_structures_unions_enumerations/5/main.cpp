#include "season.hpp"
using namespace std;

int main() {
	cout << "Hello, input seasons names from first to forth.\nfirst: ";
	string first_s, second_s, third_s, forth_s;
	cin >> first_s;
	cout << "second: ";
	cin >> second_s;
	cout << "third: ";
	cin >> third_s;
	cout << "forth: ";
	cin >> forth_s;
	
	string translations[4] = {first_s, second_s, third_s, forth_s};
	season_translator::set_translation(translations);
	season s;
	cout << "Insert current season: ";
	cin >> s;
	++s;
	cout << "Next season is: " << s << endl;
	return 0;
}
