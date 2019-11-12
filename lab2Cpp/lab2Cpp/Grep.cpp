#include "Grep.h"

Grep::Grep(std::vector<std::string>& data, const std::vector<std::string>& arguments) : word(arguments[1]), data(data)
{
}

Grep::~Grep()
{
}

void Grep::execute()
{
	std::vector<std::string>newData;
	for (size_t i = 0; i < data.size(); i++) {
		if (data[i].find(word) != std::string::npos) {
			newData.push_back(data[i]);
		}
	}
	data = newData;
}

DataType Grep::input() const
{
	return DataType::Text;
}

DataType Grep::output() const
{
	return DataType::Text;
}
