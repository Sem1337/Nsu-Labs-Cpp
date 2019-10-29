#include <iostream>

int main(int argc, char **argv) {
	/*ReadFile* workflow = new ReadFile("input/text.txt");
	workflow->execute();
	workflow->printLines();*/
	std::string workflowName = argv[1];
	std::string inFile;
	std::string outFile;
	for (int i = 0; i < argc; ++i) {
		if (!strcmp(argv[i], "-i")) {
			inFile = argv[i + 1];
		}
		if (!strcmp(argv[i], "-o")) {
			outFile = argv[i + 1];
		}
	}
	
	return 0;
}