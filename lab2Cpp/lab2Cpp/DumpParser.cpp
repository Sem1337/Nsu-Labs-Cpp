#include "DumpParser.h"

DumpParser::DumpParser(std::vector<std::string>& blockComponents) : dataToParse(blockComponents)
{
}

DumpParser::~DumpParser()
{
}


void DumpParser::parse()
{

	dataToParse.erase(dataToParse.begin());
	dataToParse.erase(dataToParse.begin());
}
