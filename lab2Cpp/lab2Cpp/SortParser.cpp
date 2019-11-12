#include "SortParser.h"

SortParser::SortParser(std::vector<std::string>& blockComponents) : dataToParse(blockComponents)
{

}

SortParser::~SortParser()
{
}

void SortParser::parse()
{
	dataToParse.erase(dataToParse.begin());
	dataToParse.erase(dataToParse.begin());
}
