#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print(const char* c_str) {
	for (;*c_str != '\0'; c_str++) {
		cout << *c_str;
	}
}

void print(const vector<int>& nums) {
	for (int num : nums) {
		cout << num << " ";
	}
}

void print(const vector<string>& words) {
	for (string word : words) {
		cout << word << " ";
	}
}

void print(const vector<const char*>& c_strs) {
	for (const char* c_word : c_strs) {
		print(c_word);
		cout << " ";
	}
}

int main() {
	string s = "this is c string";
	print(s.c_str());
	cout << endl;
	vector<int> nums { 1, 2, 3, 4 };
	print(nums);
	cout << endl;
	vector<string> words { "first", "second", "third", "forth" };
	print(words);
	cout << endl;
	vector<const char*> c_words;
	for (string word : words) {
		c_words.push_back(word.c_str());
	}

	print(c_words);
	cout << endl;
	return 0;
}
