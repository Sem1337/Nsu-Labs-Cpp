#include "SortValidator.h"

SortValidator::SortValidator(std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

SortValidator::~SortValidator()
{
}

bool SortValidator::isValid()
{
	if (blockComponents.size() == 3 + countOfArguments)return true;
	return false;
}
