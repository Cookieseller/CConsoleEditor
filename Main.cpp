#include <fstream>
#include <string>
#include <stdlib.h>

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

void readKey() {

}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Not enough arguments passed!");
		
		return 1;
	}
	
	checkFile(argv[1]);

	while (true) {
		system("cls");
		outputFile(argv[1]);
	}
}