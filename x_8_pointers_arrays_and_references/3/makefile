all: print_task usual optimized
	@echo "\n"

optimized: main.cpp
	rm -f exe.out
	@echo testing optimized build
	g++ main.cpp -std=c++20 -O2 -o exe.out
	./exe.out

usual: main.cpp
	rm -f exe.out
	@echo testing usual build:
	g++ main.cpp -std=c++20 -o exe.out
	./exe.out

print_task: task
	@echo -------------------task----------------------------------
	@cat task
	@echo -------------------output--------------------------------
