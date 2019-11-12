#include <iostream>
#include <exception>
#include "Workflow.h"
int main(int argc, char** argv) {

	std::string workFile = "work/workflow.txt";
	std::string in;
	std::string out;
	if (argc > 1) {
		workFile = argv[1];
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
				in = argv[i + 1];
			}
			if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
				out = argv[i + 1];
			}
		}
	}
	std::cout << workFile << std::endl;
	try {
		std::unique_ptr<Workflow>workFlow(new Workflow(workFile, in, out));		
	}
	catch (const std::exception & e) {
		std::cerr << e.what();
	}


	return 0;
}