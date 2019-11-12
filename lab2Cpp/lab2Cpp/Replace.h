#pragma once
#include "IWorker.h"
class Replace :
	public IWorker
{
public:
	Replace(std::vector<std::string>& data, const std::vector<std::string>& arguments);
	~Replace();
	virtual void execute() override;
	virtual DataType input() const override;
	virtual DataType output() const override;
private:
	std::string oldWord;
	std::string newWord;
	std::vector<std::string>& data;
};

