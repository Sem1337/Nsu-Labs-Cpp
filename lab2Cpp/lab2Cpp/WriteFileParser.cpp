#include "WriteFileParser.h"

WriteFileParser::WriteFileParser(std::vector<std::string>& blockComponents) : dataToParse(blockComponents)
{
	
}

WriteFileParser::~WriteFileParser()
{
}



void WriteFileParser::parse()
{
	dataToParse.erase(dataToParse.begin());
	dataToParse.erase(dataToParse.begin());
}
