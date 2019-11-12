#pragma once
#include "IWorker.h"
class Sort :
	public IWorker
{
public:
	Sort(std::vector<std::string>& data);
	~Sort();
	virtual void execute() override;
	virtual DataType input() const override;
	virtual DataType output() const override;
private:
	std::vector<std::string>& data;
};

