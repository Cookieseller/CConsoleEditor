#include <fstream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <list>
#include "Keys.h"

std::list<std::string> fileMap;

void checkFile(char *filePath) {
	std::ifstream file(filePath);
	if (!file.good()) {
		std::ofstream file(filePath);
	}
}

void readFileToMap(char *filePath) {
	std::ifstream file(filePath);
	std::string line;
	
	while (std::getline(file, line)) {
		fileMap.push_back(line);
	}
}

void outputFileMap() {
	COORD coord;
	coord.X = 1;
	coord.Y = 0;
	
	system("cls");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(consoleHandle, coord);
	
	for (auto line : fileMap) {
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

void insertNewLine() {
	POINT pos;
	GetCursorPos(&pos);
	
	auto it = std::next(fileMap.begin(), pos.y);
	fileMap.insert(it, "");
	outputFileMap();
}

int handleKeyPresses() {
	/*SHORT tabKeyState = GetAsyncKeyState( VK_TAB );
	if( ( 1 << 15 ) & tabKeyState )
	{
		if high bit is set key is pressed
	}*/
	
	int key = _getche();
	if (key == VK_RETURN) {
		insertNewLine();
	}
	if (key == VK_ESCAPE) {
		return 1;
	}
	
	return 0;
}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Not enough arguments passed!");
		
		return 1;
	}
	
	checkFile(argv[1]);
	hideCursor();
	
	readFileToMap(argv[1]);
	outputFileMap();

	while (true) {
		if (handleKeyPresses()) {
			break;
		}
	}
	
	return 0;
}