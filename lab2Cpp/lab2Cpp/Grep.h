#pragma once
#include "IWorker.h"
class Grep :
	public IWorker
{
public:
	Grep(std::vector<std::string>& data, const std::vector<std::string>& arguments);
	~Grep();
	virtual void execute() override;
	virtual DataType input() const override;
	virtual DataType output() const override;
private:
	std::string word;
	std::vector<std::string>& data;
};

