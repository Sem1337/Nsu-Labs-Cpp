#include "ReplaceValidator.h"

ReplaceValidator::ReplaceValidator(const std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

ReplaceValidator::~ReplaceValidator()
{
}

void ReplaceValidator::validation()
{
	if (blockComponents.size() < 3 + countOfArguments)throw ValidationException("too few arguments at 'replace' block");
	if (blockComponents.size() > 3 + countOfArguments)throw ValidationException("too many arguments at 'replace' block");
}
