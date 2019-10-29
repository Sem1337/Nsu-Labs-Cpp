#include "ReadFileParser.h"

ReadFileParser::ReadFileParser(std::vector<std::string>& blockComponents) : dataToParse(blockComponents)
{
}

ReadFileParser::~ReadFileParser()
{
}


void ReadFileParser::parse()
{
	dataToParse.erase(dataToParse.begin());
	dataToParse.erase(dataToParse.begin());
}
