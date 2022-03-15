all: linux windows

linux : 
	@echo "Compile for Linux"
	@gcc plateau.c -o code.out
	@echo "Done"
	@./code.out