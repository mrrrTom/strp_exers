#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

struct node {
	string* word;
	node* next;
};

node* first = nullptr;
node* last = nullptr;

void collect_nodes() {
	string input_word;
	do {
		string* cur_word = new string();
		cin >> input_word;
		*cur_word = input_word;
		node* cur_node = new node { cur_word, nullptr };
		if(!first) {
			first = cur_node;
		}
		else {
			last -> next = cur_node;
		}

		last = cur_node;
	}
	while (input_word != "Exit");
}

void print_nodes() {
	unordered_set<string> printed_words;
	node* cur = first;
	while(cur) {
		string cur_word = *(cur -> word);
		if (printed_words.find(cur_word) == printed_words.end()) {
			printed_words.insert(cur_word);
			cout << *(cur -> word) << endl;
		}

		cur = cur -> next;
	}
}

void remove_nodes() {
	node* next = first -> next;
	node* current = first;
	while(current) {
		next = current -> next;
		delete(current -> word);
		delete(current);
		current = next;
	}
}

int main() {
	collect_nodes();
	print_nodes();
	remove_nodes();
	return 0;
}
