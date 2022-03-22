all: GCC

GCC : 
	@echo "Compile for Linux"
	@gcc -o main.out ./src/main.c
	@echo "Done"
	@./main.out