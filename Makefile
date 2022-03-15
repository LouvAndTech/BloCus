all: linux

linux : 
	@echo "Compile for Linux"
	@gcc main.c -o main.out
	@echo "Done"
	@./main.out