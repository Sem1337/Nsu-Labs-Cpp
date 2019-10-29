#pragma once
#include "Validator.h"
class ReadFileValidator :
	public Validator
{
public:
	ReadFileValidator(std::vector<std::string>& blockComponents);
	~ReadFileValidator();
	virtual bool isValid() override;
private:
	std::vector<std::string>& blockComponents;
	int countOfArguments = 1;
};

