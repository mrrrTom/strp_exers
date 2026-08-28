main: main.cpp task
	@echo -------------------task----------------------------------
	@cat task
	@echo -------------------output--------------------------------
	@echo "\n"
	rm -f exe.out
	@g++ main.cpp -I ./ -std=c++20 -Wall -Weffc++ -pedantic \
	-pedantic-errors -Wextra -Waggregate-return -Wcast-align -o exe.out
	echo 'hello' > privet_file
	./exe.out 'purina' <privet_file >encoded_file
	./exe.out 'purina' <encoded_file
	@echo "\n"
