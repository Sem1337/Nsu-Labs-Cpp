#pragma once
#include "IWorker.h"
#include "ExecutionException.h"
#include "WriteFile.h"
#include "ReadFile.h"
#include "Sort.h"
#include "Replace.h"
#include "Grep.h"
#include "Dump.h"
class Scheme :
	public IWorker
{
public:
	Scheme(std::map<int, std::vector<std::string>>& blocksId, const std::list<int>& sequence, const std::string& inputFileName = "", const std::string& outputFileName = "");
	virtual ~Scheme();
	virtual void execute() override;
	virtual DataType input() const override;
	virtual DataType output() const override;
private:
	const std::string& inputFileName;
	const std::string& outputFileName;
	std::list<std::unique_ptr<IWorker>>blocks;
	std::unique_ptr<IWorker> createBlock(const std::vector<std::string>&);
	std::vector<std::string>data;
};

