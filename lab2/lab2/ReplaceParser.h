#pragma once
#include "Parser.h"
class ReplaceParser :
	public Parser
{
public:
	ReplaceParser(std::vector<std::string>& blockComponents);
	~ReplaceParser();
	virtual void parse() override;
private:
	std::vector<std::string>& dataToParse;
};

