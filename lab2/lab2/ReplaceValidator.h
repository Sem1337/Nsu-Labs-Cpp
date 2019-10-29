#pragma once
#include "Validator.h"
class ReplaceValidator :
	public Validator
{
public:
	ReplaceValidator(std::vector<std::string>& blockComponents);
	~ReplaceValidator();
	virtual bool isValid() override;
private:
	std::vector<std::string>& blockComponents;
	int countOfArguments = 2;
};

