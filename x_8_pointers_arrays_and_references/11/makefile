main: main.cpp task
	@echo -------------------task----------------------------------
	@cat task
	@echo -------------------output--------------------------------
	@echo "Unsorted\n"
	rm -f exe.out
	@g++ main.cpp -std=c++20 -Wall -Weffc++ -pedantic \
	-pedantic-errors -Wextra -Waggregate-return -Wcast-align -o exe.out
	@echo "Insert words to be printed\n"
	@./exe.out
	@echo "\n"
	@echo "Sorted\n"
	rm -f exe.out
	@g++ main_sorted.cpp -std=c++20 -Wall -Weffc++ -pedantic \
	-pedantic-errors -Wextra -Waggregate-return -Wcast-align -o exe.out
	@echo "Insert words to be printed\n"
	@./exe.out
	@echo "\n"
