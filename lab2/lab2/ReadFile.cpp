#include "ReadFile.h"

ReadFile::ReadFile(std::string fileName, std::vector<std::string>& data) : fileName(fileName) , data(data)
{
}

ReadFile::~ReadFile()
{
}

void ReadFile::execute()
{
	std::ifstream in(fileName);
	std::string nextLine;
	while (std::getline(in, nextLine)) {
		data.push_back(nextLine);
	}
	in.close();
}
