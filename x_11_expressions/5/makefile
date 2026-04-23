main: main_zero.cpp main_under.cpp main_over.cpp task
	@echo -------------------task----------------------------------
	@cat task
	@echo -------------------output--------------------------------
	@echo "\n"
	rm -f exe.out
	@echo "zero division:"
	@g++ main_zero.cpp -std=c++20 -o exe.out
	-./exe.out
	@echo "\n"
	rm -f exe.out
	@echo "underflow:"
	@g++ main_under.cpp -std=c++20 -o exe.out
	-./exe.out
	@echo "\n"
	rm -f exe.out
	@echo "overflow:"
	@g++ main_over.cpp -std=c++20 -o exe.out
	-./exe.out
	@echo "\n"
