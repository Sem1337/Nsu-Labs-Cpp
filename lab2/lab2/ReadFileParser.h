#pragma once
#include "Parser.h"
class ReadFileParser :
	public Parser
{
public:
	ReadFileParser(std::vector<std::string>& blockComponents);
	~ReadFileParser();
	virtual void parse() override;
private:
	std::vector<std::string>& dataToParse;
};

