#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct t_node {
	private:
		void collect_words(vector<string>& words_list) {
			words_list.push_back(word);
			if (left != nullptr) {
				left->collect_words(words_list);
			}

			if (right != nullptr) {
				right->collect_words(words_list);
			}
		}
	public:
	char* word;
	int count;
	t_node* left;
	t_node* right;

	t_node(string word_) : count{1}, left{nullptr}, right{nullptr} {
		word = new char[word_.length() + 1];
		char* cur = word;
		for (char symb : word_) {
			*cur = symb;
			cur++;
		}

		*(cur + word_.length()) = '\0';
	}

	void insert(string new_word) {
		if (left == nullptr) {
			t_node* new_node = new t_node(new_word);
			left = new_node;
		}
		else if (right == nullptr) {
			t_node* new_node = new t_node(new_word);
			right = new_node;
		}
		else if ((left->count) <= (right->count)) {
			left->insert(new_word);
		}
		else {
			right->insert(new_word);
		}

		count++;
	}

	void print() {
		vector<t_node*> print_list{ this };
		for (int i = 0; i < print_list.size();) {
			for(int j = i; j < print_list.size(); ++j) {
				cout << print_list[j]->word << " ";
			}

			cout << endl;
			int max_on_this_level = print_list.size();
			for(int j = i; j < max_on_this_level; ++j) {
				i++;
				if (print_list[j]->left) {
					print_list.push_back(print_list[j]->left);
				}

				if (print_list[j]->right) {
					print_list.push_back(print_list[j]->right);
				}
			}
		}
	}

	void print_alphabetical() {
		vector<string> words_list;
		collect_words(words_list);
		sort(words_list.begin(), words_list.end());
		for (string word : words_list) {
			cout << word << endl;
		}
	}

	~t_node() {
		if (left != nullptr) delete(left);
		if (right != nullptr) delete(right);
	}
};

int main (int argc, char *argv[]) {
	t_node* node = new t_node{"first"};
	node->insert("second");
	node->insert("third");
	node->print();
	cout << endl;

	node->insert("forth");
	node->insert("fifth");
	node->insert("sixth");
	node->insert("seventh");
	node->insert("eights");
	node->insert("nines");
	node->insert("tens");
	node->print();

	cout << "alphabetical:" << endl;
	node->print_alphabetical();
	return 0;
}
