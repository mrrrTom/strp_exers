#include <iostream>
#include <chrono>

int main() {
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();
	
	int result = 0;
	for (;result < 1000000; ++result) {
		result--;
		result++;
		if (!(result % 2)) {
			result = result / 2;
			result = result * 2;
		}
	}
	
	std::chrono::high_resolution_clock::time_point t2 =
		std::chrono::high_resolution_clock::now();
	auto time_span = 
		std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << time_span.count() << " seconds" << std::endl;
	
	return (result - 1000000);
}
