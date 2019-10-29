#include "Scheme.h"


Scheme::Scheme(std::map<int, std::vector<std::string>>& blocksId, std::list<int>& sequence)
{
	for (auto id : sequence) {
		blocks.push_back(createBlock(blocksId[id]));
	}
}

Scheme::~Scheme()
{
}

void Scheme::execute()
{
	for (auto block : blocks) {
		block->execute();
	}
}

IWorker* Scheme::createBlock(std::vector<std::string>& blockComponents)
{
	//if(blockComponents[0]=="writefile")
	//if (blockComponents[0] == "writefile")
	//if (blockComponents[0] == "writefile")
	//if (blockComponents[0] == "writefile")
	//if (blockComponents[0] == "writefile")
	//if (blockComponents[0] == "writefile")
	return nullptr;
}
