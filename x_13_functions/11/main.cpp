#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;
unordered_map<char, int> _commons {
	{ ' ', 41 },
	{ 'e', 40 },
	{ 't', 39 },
	{ 'a', 38 },
	{ 'o', 37 },
	{ 'i', 36 },
	{ 'n', 35 },
	{ 's', 34 },
	{ 'h', 33 },
	{ 'r', 32 },
	{ 'd', 31 },
	{ 'l', 30 },
	{ 'c', 29 },
	{ 'u', 28 },
	{ 'm', 27 },
	{ 'w', 26 },
	{ 'f', 25 },
	{ 'g', 24 },
	{ 'y', 23 },
	{ 'p', 22 },
	{ 'b', 21 },
	{ 'v', 20 },
	{ 'k', 19 },
	{ 'j', 18 },
	{ 'x', 17 },
	{ 'q', 16 },
	{ 'z', 15 },
	{ '!', 14 },
	{ '?', 13 },
	{ '.', 12 },
	{ '-', 11 },
	{ '.', 10 }
};

unordered_set<char> _top_7_commons { 'e', 't', 'a', 'o', 'i', 'n', 's' };
unordered_set<char> _bot_7_commons { 'z', 'q', 'x', 'j', 'k', 'v', 'b' };

struct key_val {
	char key;
	char val;

	key_val(char key_, char val_) : key{key_}, val{val_} {}
};

auto cmp = [] (const key_val l, const key_val r) -> bool { return (_commons[l.val] < _commons[r.val]); };
priority_queue<key_val, vector<key_val>, decltype(cmp)> try_alphabet_for_decryption(char symb) {
	priority_queue<key_val, vector<key_val>, decltype(cmp)> result {cmp};
	for (char i = 'a'; i <= 'z'; ++i) {
		char decrypted = (symb ^ i);
		if (_commons.find(decrypted) == _commons.end()) continue;
		result.push(key_val{i, decrypted});
	}

	return result;
}
string _key;
void decrypt_all_text_with_key(string& txt, string& result) {
	for(int i = 0,j = 0; i < txt.length(); ++i) {
		if (_key[j] != ' ') result += (static_cast<char>(((txt[i]) ^ (_key[j]))));
		j++;
		j = j % _key.length();
	}
}

vector<char> get_char_frequencies(string& txt) {
	unordered_map<char, int> freqs;
	unordered_set<char> encoded_symbs_unsorted;
	for (int i = 0; i < txt.length(); ++i) {
		char symb = txt[i];
		freqs[symb]++;
		encoded_symbs_unsorted.insert(symb);
	}

	auto cmp = [&freqs](const char l, const char r) -> bool { return (freqs[l] < freqs[r]); };
	priority_queue<char, vector<char>, decltype(cmp)> encoded_symbs_sorted (cmp);
	for (char symb : encoded_symbs_unsorted) {
		encoded_symbs_sorted.push(symb);
	}

	vector<char> result;
	while (encoded_symbs_sorted.size() != 0) {
		result.push_back(encoded_symbs_sorted.top());
		encoded_symbs_sorted.pop();
	}

	return result;
}

int main(int argc, char* argv[]) {
	string file_name = argv[1];
	ifstream f(file_name);
	string input_text;
	char input_symb;
	while (f.get(input_symb)) {
		input_text += input_symb;
	}

	vector<char> chars_by_freqs = get_char_frequencies(input_text);
	for (char symb : chars_by_freqs) {
		cout << "encoded: " << symb
			<< " decrypt variants: " ;
		auto symb_decryption_variants = try_alphabet_for_decryption(symb);
		while (symb_decryption_variants.size() != 0) {
			auto decr_pair = symb_decryption_variants.top();
			cout << "(" << decr_pair.key << ")->" << decr_pair.val << "; ";
			symb_decryption_variants.pop();
		}

		cout << endl;
	}

	// todo we need to calculate for each variant with shift - how much top 5 letters are really in top
	// and how much bottom 5 letters are in bot
	while (true) {
		_key = "";
		cout << "put <string shift_left shift_right>:";
		string s;
		int shift_l;
		int shift_r;
		cin >> s;
		cin >> shift_l;
		cin >> shift_r;
		for (int i = 0; i < shift_l; ++i) {
			_key += ' ';
		}

		_key += s;

		for (int i = 0; i < shift_r; ++i) {
			_key += ' ';
		}

		string decryption_result;
		decrypt_all_text_with_key(input_text, decryption_result);
		vector<char> symb_freqs = get_char_frequencies(decryption_result);
		int top_count = 0;
		int bot_count = 0;
		for (int i = 0; i < 10; ++i) {
			if (_top_7_commons.find(symb_freqs[i]) != _top_7_commons.end()) top_count++;
		}

		for (int i = 20; i < symb_freqs.size(); ++i) {
			if (_bot_7_commons.find(symb_freqs[i]) != _bot_7_commons.end()) bot_count++;
		}

		cout << "top matches: " << top_count << " bot matches: " << bot_count << endl;
	}
	return 0;
}
