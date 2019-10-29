#include "ReplaceValidator.h"

ReplaceValidator::ReplaceValidator(std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

ReplaceValidator::~ReplaceValidator()
{
}

bool ReplaceValidator::isValid()
{
	if (blockComponents.size() == 3 + countOfArguments)return true;
	return false;
}
