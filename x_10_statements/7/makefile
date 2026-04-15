main: main.cpp task
	@echo -------------------task----------------------------------
	@cat task
	@echo -------------------output--------------------------------
	@echo "\n"
	rm -f exe.out
	@g++ main.cpp -std=c++20 -Wall -Weffc++ -pedantic \
	-pedantic-errors -Wextra -Waggregate-return -Wcast-align -o exe.out
	./exe.out
	@echo "\n"
