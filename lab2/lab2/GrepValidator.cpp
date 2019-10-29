#include "GrepValidator.h"

GrepValidator::GrepValidator(std::vector<std::string>& blockComponents) : blockComponents(blockComponents)
{
}

GrepValidator::~GrepValidator()
{
}

bool GrepValidator::isValid()
{
	if (blockComponents.size() == 3 + countOfArguments)return true;
	return false;
}
