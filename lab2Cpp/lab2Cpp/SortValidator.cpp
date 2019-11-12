#include "SortValidator.h"

SortValidator::SortValidator(const std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

SortValidator::~SortValidator()
{
}

void SortValidator::validation()
{
	if (blockComponents.size() < 3 + countOfArguments)throw ValidationException("too few arguments at 'sort' block");
	if (blockComponents.size() > 3 + countOfArguments)throw ValidationException("too many arguments at 'sort' block");
}
