#include "ReadFile.h"

ReadFile::ReadFile(std::vector<std::string>& data, const std::vector<std::string>& arguments) : fileName(arguments[1]), data(data)
{
}

ReadFile::~ReadFile()
{
}

void ReadFile::execute()
{

	data.clear();
	std::ifstream in;

	in.open(fileName);
	//std::cout << std::string("Exception thrown while handling " + fileName + " file");
	if (!in)throw ExecutionException("Exception thrown while handling file");
	std::string nextLine;
	while (std::getline(in, nextLine)) {
		data.push_back(nextLine);
	}
	in.close();

	

}

enum DataType ReadFile::input() const
{
	return DataType::Void;
}

enum DataType ReadFile::output() const
{
	return DataType::Text;
}
