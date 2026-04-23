#ifndef DV_STR_HPP
#define DV_STR_HPP
#define C_STR_END_SYMB '\0'
using namespace std;
namespace dv_str {
int strlen(char* str) {
	int result = 0;
	while (*str != C_STR_END_SYMB) {
		result++;
		str++;
	}

	return result;
}

bool strcpy(char* from, char* to) {
	while (*from != C_STR_END_SYMB) {
		if (*to == C_STR_END_SYMB) return false;
		*to = *from;
		to++;
		from++;
	}
	
	return true;
}

int strcmp(char* left, char* right) {
	while (*left != C_STR_END_SYMB) {
		if (*right == C_STR_END_SYMB) return 1;
		if (static_cast<int>(*left) < static_cast<int>(*right)) return 1;
		if (static_cast<int>(*left) > static_cast<int>(*right)) return -1;
		left++;
		right++;
	}

	if (*right == C_STR_END_SYMB) return 0;
	return -1;
}
}
#endif
