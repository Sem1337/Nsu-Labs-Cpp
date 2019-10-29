#pragma once
#include "IWorker.h"
class Scheme :
	public IWorker
{
public:
	Scheme(std::map<int, std::vector<std::string>>& blocksId, std::list<int>& sequence);
	virtual ~Scheme();
	virtual void execute() override;
private:
	std::list<IWorker*>blocks;
	IWorker* createBlock(std::vector<std::string>&);
	std::vector<std::string>data;
};

