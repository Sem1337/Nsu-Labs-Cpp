#pragma once
#include "Parser.h"
class SortParser :
	public Parser
{
public:
	SortParser(std::vector<std::string>& blockComponents);
	~SortParser();
	virtual void parse() override;
private:
	std::vector<std::string>& dataToParse;
};

