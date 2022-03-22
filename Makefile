all: linux

linux : 
	@echo "Compile for Linux"
	@gcc ./src/main.c -o main.out
	@echo "Done"
	@./main.out