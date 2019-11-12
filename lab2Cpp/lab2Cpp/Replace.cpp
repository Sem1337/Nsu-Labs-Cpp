#include "Replace.h"

Replace::Replace(std::vector<std::string>& data, const std::vector<std::string>& arguments) 
	: oldWord(arguments[1]) , newWord(arguments[2]) , data(data)
{
}

Replace::~Replace()
{
}

void Replace::execute()
{
	for (auto &line : data) {
		do {
			int currentPos = 0;
			size_t nextMatch = line.find(oldWord, currentPos);
			if (nextMatch != std::string::npos) {
				currentPos = nextMatch + newWord.length();
				line.erase(nextMatch, oldWord.length());
				line.insert(nextMatch, newWord);
			}
			else {
				break;
			}
		} while (true);
	}
}

enum DataType Replace::input() const
{
	return DataType::Text;
}

enum DataType Replace::output() const
{
	return DataType::Text;
}
