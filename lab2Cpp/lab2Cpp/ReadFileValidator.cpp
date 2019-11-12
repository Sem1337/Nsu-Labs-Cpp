#include "ReadFileValidator.h"

ReadFileValidator::ReadFileValidator(const std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

ReadFileValidator::~ReadFileValidator()
{
}

void ReadFileValidator::validation()
{
	if (blockComponents.size() < 3 + countOfArguments)throw ValidationException("too few arguments at 'readfile' block");
	if (blockComponents.size() > 3 + countOfArguments)throw ValidationException("too many arguments at 'readfile' block");

}
