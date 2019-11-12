#include "GrepValidator.h"

GrepValidator::GrepValidator(const std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

GrepValidator::~GrepValidator()
{
}

void GrepValidator::validation()
{
	if (blockComponents.size() < 3 + countOfArguments)throw ValidationException("too few arguments at 'grep' block");
	if (blockComponents.size() > 3 + countOfArguments)throw ValidationException("too many arguments at 'grep' block");
}
