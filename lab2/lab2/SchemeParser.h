#pragma once
#include "Parser.h"
#include "WriteFileParser.h"
#include "ReadFileParser.h"
#include "SortParser.h"
#include "GrepParser.h"
#include "ReplaceParser.h"
#include "DumpParser.h"
class SchemeParser :
	public Parser
{
public:
	SchemeParser(std::vector<std::string>& data);
	~SchemeParser();
	const std::list<int>& getParsedSequence();
	const std::map<int, std::vector<std::string>>& getBlocksDescription();
	virtual void parse() override;

private:
	Parser* createBlockParser(std::vector<std::string>&);
	int idToInt(std::string id);
	std::vector<std::string>& data;
	std::map<int, std::vector<std::string>>blocks;
	std::list<int>order;
};

