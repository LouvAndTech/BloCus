all: GCC

GCC : 
	@echo "Compile for Linux..."
	@gcc -o main.out ./src/main.c
	@echo "Done"
	@./main.out

SAVE : 
	@echo "Compile for Linux..."
	@gcc -o save.out ./src/save.c ./src/sqlite/sqlite3.c -lpthread -ldl
	@echo "Done"
	@./save.out

TEST:
	@echo "Compile for Linux..."
	@gcc -o test.out ./test.c
	@echo "Done"
	@./test.out