#include "DumpValidator.h"

DumpValidator::DumpValidator(std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

DumpValidator::~DumpValidator()
{
}

bool DumpValidator::isValid()
{
	if (blockComponents.size() == 3 + countOfArguments)return true;
	return false;
}
