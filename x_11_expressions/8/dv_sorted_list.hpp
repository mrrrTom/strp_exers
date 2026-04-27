#ifndef DV_SORTED_LIST_HPP
#define DV_SORTED_LIST_HPP
using namespace std;

namespace dv_sorted_list {

	struct node {
		node* next;
		double val;
	};

	struct sorted_list {
		private:
			unsigned int _count;
			node* _head;
			double _sum;
			double get(int index);
		public:
			sorted_list(void);
			double sum(void);
			double mean(void);
			double median(void);
			void insert(double val);
			~sorted_list();
	};

	sorted_list::sorted_list() {
		_count = 0;
		_sum = 0;
		_head = nullptr;
	}

	double sorted_list::sum() {
		return _sum;
	}

	double sorted_list::mean() {
		return (_sum / _count);
	}

	double sorted_list::median() {
		if ((_count % 2) == 0) {
			int left_index = (_count / 2) - 1;
			int right_index = left_index + 1;
			return ((this -> get(left_index)
						+ this -> get(right_index)) / 2);
		}	
		else {
			int median_index = (_count / 2);
			return this -> get(median_index);
		}
	}

	double sorted_list::get(int index) {
		node* cur = _head;
		for (int i = 0; i < index; i++) cur = cur -> next;
		return cur -> val;
	}

	void sorted_list::insert(double val) {
		_count++;
		_sum += val;
		node* nnode = new node();
		nnode -> val = val;
		if (!_head) {
			_head = nnode;
			return;
		}
		
		node* left = _head;
		node* right = _head -> next;
		while (left && right &&
				(right -> val < val)) {
			left = left -> next;
			right = right -> next;
		}
		
		node* temp = left -> next;
		left -> next = nnode;
		nnode -> next = temp;
	}

	sorted_list::~sorted_list() {
		while (_head) {
			node* temp = _head -> next;
			delete(_head);
			_head = temp;
		}
	}
}
#endif
