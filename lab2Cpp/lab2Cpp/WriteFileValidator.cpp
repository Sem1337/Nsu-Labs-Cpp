#include "WriteFileValidator.h"

WriteFileValidator::WriteFileValidator(const std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

WriteFileValidator::~WriteFileValidator()
{
}

void WriteFileValidator::validation()
{
	if (blockComponents.size() < 3 + countOfArguments)throw ValidationException("too few arguments at 'writefile' block");
	if (blockComponents.size() > 3 + countOfArguments)throw ValidationException("too many arguments at 'writefile' block");
}
