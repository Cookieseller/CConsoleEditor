#include <fstream>
#include <string>

void outputFile(char *filePath) {
	std::ifstream file(filePath);
	std::string line;

	while (std::getline(file, line)) {
		printf("%s\r\n", line.c_str());
	}
}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Not enough arguments passed!");
		
		return 1;
	}
	
	outputFile(argv[1]);
}