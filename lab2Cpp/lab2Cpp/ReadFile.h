#pragma once
#include "IWorker.h"
class ReadFile :
	public IWorker
{
public:
	ReadFile(std::vector<std::string>& data, const std::vector<std::string>& arguments);
	virtual ~ReadFile();
	virtual void execute() override;
	virtual DataType input() const override;
	virtual DataType output() const override;
private:
	std::string fileName;
	std::vector<std::string>& data;
};

