#include "SchemeParser.h"

SchemeParser::SchemeParser(std::vector<std::string>& data) : data(data)
{
}



SchemeParser::~SchemeParser()
{
}

std::list<int>& SchemeParser::getParsedSequence()
{
	return order;
}

std::map<int, std::vector<std::string>>& SchemeParser::getBlocksDescription()
{
	return blocks;
}

void SchemeParser::parse()
{
	size_t currentString = 1;
	size_t countOfStr = data.size();
	while (data[currentString] != "csed") {
		std::vector<std::string> tokenizedBlock = StrExtd::tokenize(data[currentString]);
		std::unique_ptr<Parser> blockParser = createBlockParser(tokenizedBlock);
		int blockId = idToInt(tokenizedBlock[0]);
		blockParser->parse();
		blocks[blockId] = tokenizedBlock;
		currentString++;
	}
	currentString++;
	if (currentString < countOfStr) {
		std::vector<std::string>tokenizedSequence = StrExtd::tokenize(data[currentString]);
		for (size_t i = 0; i < tokenizedSequence.size();i++) {
			if ((i & 1) == 0) {
				order.push_back(idToInt(tokenizedSequence[i]));
			}
		}
	}
}



std::unique_ptr<Parser> SchemeParser::createBlockParser(std::vector<std::string>& blockComponents)
{
	if (blockComponents[2] == "writefile")return std::unique_ptr<Parser>(new WriteFileParser(blockComponents));
	if (blockComponents[2] == "readfile")return std::unique_ptr<Parser>(new ReadFileParser(blockComponents));
	if (blockComponents[2] == "replace")return std::unique_ptr<Parser>(new ReplaceParser(blockComponents));
	if (blockComponents[2] == "dump")return std::unique_ptr<Parser>(new DumpParser(blockComponents));
	if (blockComponents[2] == "grep")return std::unique_ptr<Parser>(new GrepParser(blockComponents));
	if (blockComponents[2] == "sort")return std::unique_ptr<Parser>(new SortParser(blockComponents));
	return nullptr;
}

int SchemeParser::idToInt(std::string id)
{
	int idLen = id.length();
	int result = 0;
	for (int i = 0; i < idLen; i++) {
		result *= 10;
		result += (id[i] - '0');
	}
	return result;
}
