#pragma once
#include "Validator.h"
class DumpValidator :
	public Validator
{
public:
	DumpValidator(std::vector<std::string>& blockComponents);
	~DumpValidator();
	virtual bool isValid() override;
private:
	std::vector<std::string>& blockComponents;
	int countOfArguments = 1;
};

