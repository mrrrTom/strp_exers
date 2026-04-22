main: main.cpp task
	@echo -------------------task----------------------------------
	@cat task
	@echo -------------------output--------------------------------
	@echo "\n"
	@echo "g++ compiler:"
	rm -f exe.out
	@g++ main.cpp -o exe.out
	./exe.out
	@echo "\n"
	rm -f exe.out
	@echo "clang++ compiler:"
	@clang++ main.cpp -o exe.out
	./exe.out
	@echo "\n"
