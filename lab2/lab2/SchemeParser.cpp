#include "SchemeParser.h"

SchemeParser::SchemeParser(std::vector<std::string>& data) : data(data)
{
}



SchemeParser::~SchemeParser()
{
}

const std::list<int>& SchemeParser::getParsedSequence()
{
	return order;
}

const std::map<int, std::vector<std::string>>& SchemeParser::getBlocksDescription()
{
	return blocks;
}

void SchemeParser::parse()
{
	int currentString = 1;
	int countOfStr = data.size();
	while (data[currentString] != "csed") {
		std::vector<std::string>tokenizedBlock = StrExtd::tokenize(data[currentString]);
		Parser* blockParser = createBlockParser(tokenizedBlock);
		int blockId = idToInt(tokenizedBlock[0]);
		blockParser->parse();
		blocks[blockId] = tokenizedBlock;
		currentString++;
	}
	currentString++;
	if (currentString < countOfStr) {
		std::vector<std::string>tokenizedSequence = StrExtd::tokenize(data[currentString]);
		for (int i = 0; i < tokenizedSequence.size();i++) {
			if ((i & 1) == 0) {
				order.push_back(idToInt(tokenizedSequence[i]));
			}
		}
	}
}



Parser* SchemeParser::createBlockParser(std::vector<std::string>& blockComponents)
{
	if (blockComponents[2] == "writefile")return new WriteFileParser(blockComponents);
	if (blockComponents[2] == "readfile")return new ReadFileParser(blockComponents);
	if (blockComponents[2] == "replace")return new ReplaceParser(blockComponents);
	if (blockComponents[2] == "dump")return new DumpParser(blockComponents);
	if (blockComponents[2] == "grep")return new GrepParser(blockComponents);
	if (blockComponents[2] == "sort")return new SortParser(blockComponents);
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
