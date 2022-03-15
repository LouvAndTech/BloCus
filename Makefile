all: linux windows

linux : 
	@echo "Compile for Linux"
	@gcc CodeSource.c -o code.out
	@echo "Done"

windows :
	@echo "Compile for windows"
	@x86_64-w64-mingw32-gcc CodeSource.c -o Game.exe
	@echo "Done"