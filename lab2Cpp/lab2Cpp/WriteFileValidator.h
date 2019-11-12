#pragma once
#include "Validator.h"
class WriteFileValidator :
	public Validator
{
public:
	WriteFileValidator(const std::vector<std::string>& blockComponents);
	~WriteFileValidator();
	virtual void validation() override;
private:
	const std::vector<std::string>& blockComponents;
	size_t countOfArguments = 1;
};

