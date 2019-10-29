#pragma once
#include "IWorker.h"
class ReadFile :
	public IWorker
{
public:
	ReadFile(std::string fileName, std::vector<std::string>& data);
	virtual ~ReadFile();
	virtual void execute() override;
private:
	std::string fileName;
	std::vector<std::string>& data;
};

