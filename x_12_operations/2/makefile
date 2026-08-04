main: empty_main.cpp value_main.cpp task
	@echo -------------------task----------------------------------
	@cat task
	@echo -------------------output--------------------------------
	@echo "\n"
	@rm -f exe.out
	@g++ empty_main.cpp -I ./ -std=c++20 -o exe.out 
	./exe.out 
	@rm -f exe.out
	@g++ value_main.cpp -I ./ -std=c++20 -o exe.out
	./exe.out 
	@echo "\n"
