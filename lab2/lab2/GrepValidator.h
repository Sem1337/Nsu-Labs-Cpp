#pragma once
#include "Validator.h"
class GrepValidator :
	public Validator
{
public:
	GrepValidator(std::vector<std::string>& blockComponents);
	~GrepValidator();
	virtual bool isValid() override;
private:
	std::vector<std::string>& blockComponents;
	int countOfArguments = 1;
};

