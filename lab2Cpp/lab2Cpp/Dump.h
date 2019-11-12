#pragma once
#include "IWorker.h"
#include "WriteFile.h"
class Dump :
	public IWorker
{
public:
	Dump(const std::vector<std::string>& data, const std::vector<std::string>& arguments);
	~Dump();
	virtual void execute() override;
	virtual DataType input() const override;
	virtual DataType output() const override;
private:
	std::string fileName;
	const std::vector<std::string>& data;
};

