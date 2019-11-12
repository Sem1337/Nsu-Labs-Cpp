#include "DumpValidator.h"

DumpValidator::DumpValidator(const std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

DumpValidator::~DumpValidator()
{
}

void DumpValidator::validation()
{
	if (blockComponents.size() < 3 + countOfArguments)throw ValidationException("too few arguments at 'dump' block");
	if (blockComponents.size() > 3 + countOfArguments)throw ValidationException("too many arguments at 'dump' block");
}
