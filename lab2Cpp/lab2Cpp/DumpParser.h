#pragma once
#include "Parser.h"
class DumpParser :
	public Parser
{
public:
	DumpParser(std::vector<std::string>& blockComponents);
	~DumpParser();
	virtual void parse() override;
private:
	std::vector<std::string>& dataToParse;
};

