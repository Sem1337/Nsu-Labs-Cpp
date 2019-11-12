#pragma once
#include "Validator.h"
class ReplaceValidator :
	public Validator
{
public:
	ReplaceValidator(const std::vector<std::string>& blockComponents);
	~ReplaceValidator();
	virtual void validation() override;
private:
	const std::vector<std::string>& blockComponents;
	size_t countOfArguments = 2;
};

