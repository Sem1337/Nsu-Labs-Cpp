#pragma once
#include "Parser.h"
class GrepParser :
	public Parser
{
public:
	GrepParser(std::vector<std::string>& blockComponents);
	~GrepParser();
	virtual void parse() override;
private:
	std::vector<std::string>& dataToParse;
};

