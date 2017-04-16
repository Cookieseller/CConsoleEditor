#include <fstream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <list>
#include <iostream>

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
	COORD coord = {0, 0};
	
	system("cls");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(consoleHandle, coord);
	
	for (auto it = fileMap.begin(); it != fileMap.end(); ++it) {
		std::cout << *it;
		if (it != std::prev(fileMap.end())) {
			std::cout << "\r\n";
		}
	}
	coord = {0, 0};
	SetConsoleCursorPosition(consoleHandle, coord);
}

void showCursor() {
	CONSOLE_CURSOR_INFO info;
	info.bVisible = TRUE;
	info.dwSize = 25;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &info);
}

void insertNewLine() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		int x = csbi.dwCursorPosition.X;
        int y = csbi.dwCursorPosition.Y;

		auto it = std::next(fileMap.begin(), y);
		if (x > 0 && it->length() > 0 && x  < it->length()) {
			auto stay = it->substr(0, x);
			auto nextLine = it->substr(x);
			
			*it = stay;
			fileMap.insert(++it, nextLine);
		} else if (x == 0) {
			fileMap.insert(it, "");
		} else if (x > it->length()) {
			fileMap.insert(++it, "");
		}
		outputFileMap();
		
		COORD coord = {0, (SHORT)++y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
}

void moveCursor(auto movePosition) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		int x = csbi.dwCursorPosition.X;
        int y = csbi.dwCursorPosition.Y;
		
		movePosition(x, y);
		
		COORD coord = {(SHORT)x, (SHORT)y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
}

void moveToBOL() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		int y = csbi.dwCursorPosition.Y;
		COORD coord = {(SHORT)0, (SHORT)y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
}

void moveToEOL() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		int y = csbi.dwCursorPosition.Y;
		int x = csbi.dwCursorPosition.Y;
		
		auto it = std::next(fileMap.begin(), y);
		
		COORD coord = {(SHORT)it->length(), (SHORT)y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
}

int handleKeyPresses() {
	/*SHORT tabKeyState = GetAsyncKeyState( VK_TAB );
	if( ( 1 << 15 ) & tabKeyState )
	{
		if high bit is set key is pressed
	}*/
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int x = csbi.dwCursorPosition.X;
	int y = csbi.dwCursorPosition.Y;

	int key = _getch();
	if (key == 0 || key == 0xE0) { // Arrow keys must be read twice, the first _getche just returns one of these two values
		key = _getch();
	}
	if (key == VK_RETURN) {
		insertNewLine();
	} else if (key == VK_ESCAPE) {
		return 1;
	} else if (key == (int) MapVirtualKey(VK_UP, MAPVK_VK_TO_VSC)) {
		moveCursor([] (int &x, int &y) {if (y > 0) y--;});
	} else if (key == (int) MapVirtualKey(VK_DOWN, MAPVK_VK_TO_VSC)) {
		moveCursor([] (int &x, int &y) {y++;});
	} else if (key == (int) MapVirtualKey(VK_LEFT, MAPVK_VK_TO_VSC)) {
		moveCursor([] (int &x, int &y) {if (x > 0) x--;});
	} else if (key == (int) MapVirtualKey(VK_RIGHT, MAPVK_VK_TO_VSC)) {
		moveCursor([] (int &x, int &y) {x++;});
	} else if (key == (int) MapVirtualKey(VK_END, MAPVK_VK_TO_VSC)) {
		moveToEOL();
	} else if (key == (int) MapVirtualKey(VK_HOME, MAPVK_VK_TO_VSC)) {
		moveToBOL();
	}	else if (iswascii(key) && isprint(key)) {
		printf("%c", key);
	}
	return 0;
}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Not enough arguments passed!");
		
		return 1;
	}
	
	checkFile(argv[1]);
	showCursor();
	
	readFileToMap(argv[1]);
	outputFileMap();

	while (true) {
		if (handleKeyPresses()) {
			break;
		}
	}
	
	system("cls");
	return 0;
}