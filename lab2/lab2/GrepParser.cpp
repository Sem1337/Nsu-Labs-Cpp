#include "GrepParser.h"

GrepParser::GrepParser(std::vector<std::string>& blockComponents) : dataToParse(blockComponents)
{
}

GrepParser::~GrepParser()
{
}


void GrepParser::parse()
{
	dataToParse.erase(dataToParse.begin());
	dataToParse.erase(dataToParse.begin());
}
