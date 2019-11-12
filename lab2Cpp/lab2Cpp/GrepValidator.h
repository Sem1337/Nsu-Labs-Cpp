#pragma once
#include "Validator.h"
class GrepValidator :
	public Validator
{
public:
	GrepValidator(const std::vector<std::string>& blockComponents);
	~GrepValidator();
	virtual void validation() override;
private:
	const std::vector<std::string>& blockComponents;
	size_t countOfArguments = 1;
};

