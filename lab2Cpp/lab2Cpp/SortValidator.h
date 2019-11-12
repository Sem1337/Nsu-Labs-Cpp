#pragma once
#include "Validator.h"
class SortValidator :
	public Validator
{
public:
	SortValidator(const std::vector<std::string>& blockComponents);
	~SortValidator();
	virtual void validation() override;
private:
	const std::vector<std::string>& blockComponents;
	size_t countOfArguments = 0;
};

