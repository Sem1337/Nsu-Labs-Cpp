#pragma once
#include "Parser.h"
class WriteFileParser :
	public Parser
{
public:
	WriteFileParser(std::vector<std::string>& blockComponents);
	~WriteFileParser();
	virtual void parse() override;
private:
	std::vector<std::string>& dataToParse;
};

