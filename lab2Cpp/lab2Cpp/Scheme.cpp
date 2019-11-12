#include "Scheme.h"


Scheme::Scheme(std::map<int, std::vector<std::string>>& blocksId, const std::list<int>& sequence,const std::string& inputFileName,const std::string& outputFileName)
	: inputFileName(inputFileName), outputFileName(outputFileName)
{
	if (!inputFileName.empty()) {
		blocks.push_back(createBlock(std::vector<std::string>() = { "readfile", inputFileName }));
	}
	for (auto id : sequence) {
		blocks.push_back(createBlock(blocksId[id]));
	}
	if (!outputFileName.empty()) {
		blocks.push_back(createBlock(std::vector<std::string>() = { "writefile", outputFileName }));
	}
}

Scheme::~Scheme()
{
}

void Scheme::execute()
{
	if (blocks.empty())return;
	if (dynamic_cast<ReadFile*>(blocks.front().get()) == nullptr) {
		throw ExecutionException("Incorrect order of blocks");
	}
	else if (dynamic_cast<WriteFile*>(blocks.back().get()) == nullptr) {
		throw ExecutionException("Incorrect order of blocks");
	}
	auto readBlock = blocks.begin();
	(*readBlock)->execute();
	auto writeBlock = --blocks.end();
	DataType prevBlockOutput = (*readBlock)->output();
	for (auto block = ++readBlock; block != writeBlock; ++block) {
		if ((*block)->input() != prevBlockOutput) {
			throw ExecutionException("Incorrect order of blocks");
		}
		(*block)->execute();
		prevBlockOutput = (*block)->output();
	}
	if ((*writeBlock)->input() != prevBlockOutput) {
		throw ExecutionException("Incorrect order of blocks");
	}
	(*writeBlock)->execute();
}

enum DataType Scheme::input() const
{
	return DataType::Void;
}

enum DataType Scheme::output() const
{
	return DataType::Void;
}

std::unique_ptr<IWorker> Scheme::createBlock(const std::vector<std::string>& blockComponents)
{
	if (blockComponents[0] == "writefile")return std::unique_ptr<IWorker>(new WriteFile(data, blockComponents));
	if (blockComponents[0] == "readfile")return std::unique_ptr<IWorker>(new ReadFile(data, blockComponents));
	if (blockComponents[0] == "replace")return std::unique_ptr<IWorker>(new Replace(data, blockComponents));
	if (blockComponents[0] == "grep")return std::unique_ptr<IWorker>(new Grep(data, blockComponents));
	if (blockComponents[0] == "sort")return std::unique_ptr<IWorker>(new Sort(data));
	if (blockComponents[0] == "dump")return std::unique_ptr<IWorker>(new Dump(data, blockComponents));
	return nullptr;
}
