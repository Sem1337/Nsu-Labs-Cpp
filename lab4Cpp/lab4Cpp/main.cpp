#include <iostream>
#include <tuple>
#include <fstream>
#include <ostream>
#include <vector>
#include "CSVParser.h"




int main(int argc, char **argv) {

	std::ifstream file("input.csv");
	CSVParser<std::string, int, double, int> parser(file, 1, ';');
	for (auto rs : parser) {
		std::cout << rs << std::endl;
	}

	return 0;
}