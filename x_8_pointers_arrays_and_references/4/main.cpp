#include <iostream>

int dif_positions(char* left, char* right) {
	int result = std::abs(right - left);
	return result ? --result : result;
}

int main() {
	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'j', 'k' };
	
	char* r_ptr = arr + 3;
	std::cout << *r_ptr << std::endl;
	
	std::cout << dif_positions(arr, r_ptr);
	return 0;
}
