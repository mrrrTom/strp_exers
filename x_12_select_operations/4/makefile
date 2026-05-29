main: main.cpp task
	@echo -------------------task----------------------------------
	@cat task
	@echo -------------------output--------------------------------
	@echo "\n"
	rm -f exe.out
	g++ main.cpp -DUSING -I ./ -std=c++26 -o exe.out
	./exe.out
	rm -f exe.out
	g++ main.cpp -DTEMPLATE -I ./ -std=c++26 -o exe.out
	./exe.out
	rm -f exe.out
	g++ main.cpp -DAUTO -I ./ -std=c++26 -o exe.out
	./exe.out
	@echo "\n"
