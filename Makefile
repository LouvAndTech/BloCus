all: GCC

GCC : 
	@echo "Compile for Linux"
	@gcc -o save.out ./src/save.c ./src/sqlite/sqlite3.c -lpthread -ldl
	@echo "Done"
	@./save.out