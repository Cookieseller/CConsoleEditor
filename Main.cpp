#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>

void checkFile(char *filePath) {
	std::ifstream file(filePath);
	if (!file.good()) {
		std::ofstream file(filePath);
	}
}

void outputFile(char *filePath) {
	std::ifstream file(filePath);
	std::string line;

	while (std::getline(file, line)) {
		printf("%s\r\n", line.c_str());
	}
}

void hideCursor() {
	CONSOLE_CURSOR_INFO info;
	info.bVisible = FALSE;
	info.dwSize = 100;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &info);
}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Not enough arguments passed!");
		
		return 1;
	}
	
	checkFile(argv[1]);
	hideCursor();

	COORD coord;
	coord.X = 0;
	coord.Y = 0;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	while (true) {
		SetConsoleCursorPosition(consoleHandle, coord);
		outputFile(argv[1]);
	}
}