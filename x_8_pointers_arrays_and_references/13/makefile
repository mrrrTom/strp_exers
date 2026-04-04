main: main_ptr.cpp main_ind.cpp task
	@echo -------------------task----------------------------------
	@cat task
	@echo -------------------output--------------------------------
	@echo "\n"
	@g++ -S main_ptr.cpp -o main_ptr.s
	@echo "ptr loop"
	@cat main_ptr.s
	@g++ -S main_ind.cpp -o main_ind.s
	@echo "index loop"
	@cat main_ind.s
	@echo "\n"
