#pragma once
#include "Validator.h"
class ReadFileValidator :
	public Validator
{
public:
	ReadFileValidator(const std::vector<std::string>& blockComponents);
	~ReadFileValidator();
	virtual void validation() override;
private:
	const std::vector<std::string>& blockComponents;
	size_t countOfArguments = 1;
};

