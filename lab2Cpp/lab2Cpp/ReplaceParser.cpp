#include "ReplaceParser.h"

ReplaceParser::ReplaceParser(std::vector<std::string>& blockComponents) : dataToParse(blockComponents)
{
}

ReplaceParser::~ReplaceParser()
{
}



void ReplaceParser::parse()
{
	dataToParse.erase(dataToParse.begin());
	dataToParse.erase(dataToParse.begin());
}
