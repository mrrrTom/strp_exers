#include <iostream>
#include <limits>

int main() {
	std::cout << (std::numeric_limits<char>::is_signed ? "signed" : "unsigned");
	return 0;
}
