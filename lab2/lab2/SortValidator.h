#pragma once
#include "Validator.h"
class SortValidator :
	public Validator
{
public:
	SortValidator(std::vector<std::string>& blockComponents);
	~SortValidator();
	virtual bool isValid() override;
private:
	std::vector<std::string>& blockComponents;
	int countOfArguments = 0;
};

