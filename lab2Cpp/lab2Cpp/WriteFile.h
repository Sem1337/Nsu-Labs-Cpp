#pragma once
#include "IWorker.h"
class WriteFile :
	public IWorker
{
public:
	WriteFile(const std::vector<std::string>& data, const std::vector<std::string>& arguments);
	~WriteFile();
	virtual void execute() override;
	virtual DataType input() const override;
	virtual DataType output() const override;
private:
	std::string fileName;
	const std::vector<std::string>& data;
};

