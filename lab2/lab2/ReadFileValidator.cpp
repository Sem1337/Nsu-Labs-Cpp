#include "ReadFileValidator.h"

ReadFileValidator::ReadFileValidator(std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

ReadFileValidator::~ReadFileValidator()
{
}

bool ReadFileValidator::isValid()
{
	if (blockComponents.size() == 3 + countOfArguments)return true;
	return false;
}
