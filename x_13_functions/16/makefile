main: main.cpp task
	@echo -------------------task----------------------------------
	@cat task
	@echo -------------------output--------------------------------
	@echo "\n"
	rm -f exe.out
	@echo -e "#define pi 3.1415926\n using namespace std;\n int main() {\n cout << pi;\n return 0;\n }" > test.cpp
	@echo "before macro"
	@cat test.cpp
	@g++ main.cpp -I ./ -std=c++20 -o exe.out
	./exe.out <test.cpp
	@echo "\n"
