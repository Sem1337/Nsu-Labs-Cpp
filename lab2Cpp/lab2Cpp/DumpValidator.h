#pragma once
#include "Validator.h"
class DumpValidator :
	public Validator
{
public:
	DumpValidator(const std::vector<std::string>& blockComponents);
	~DumpValidator();
	virtual void validation() override;
private:
	const std::vector<std::string>& blockComponents;
	size_t countOfArguments = 1;
};

