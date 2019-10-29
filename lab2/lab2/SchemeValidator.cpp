#include "SchemeValidator.h"

SchemeValidator::SchemeValidator(const std::vector<std::string>& data) : data(data)
{
}

SchemeValidator::~SchemeValidator()
{
}

bool SchemeValidator::isValid()
{
	if (data.size() < 2)return false;
	if (data[0] != "desc")return false;                //desc doesn't exist
	int currentString = 1;
	int countOfStr = data.size();
	while (currentString < countOfStr && data[currentString] != "csed") {
		if (!isValidBlock(data[currentString], currentString))return false;
		currentString++;
	}
	if (currentString == countOfStr)return false;    // csed doesn't exist
	if (++currentString == countOfStr)return true;
	std::vector<std::string> sequenceComponents = StrExtd::tokenize(data[currentString]);
	for (int i = 0; i < sequenceComponents.size(); i++) {
		if (i & 1) {
			if (sequenceComponents[i] != "->")return false;
		}
		else {
			if (idOfBlocks[sequenceComponents[i]] != 1)return false;
		}
	}
	
	if (++currentString == countOfStr)return true;
	return false;
}

bool SchemeValidator::isValidBlock(const std::string& block, int num)
{
	std::vector<std::string> blockComponents = StrExtd::tokenize(block);
	if (blockComponents.size() < 3)return false;
	if (blockComponents[1] != "=")return false;
	for (int i = 0; i < blockComponents[0].length(); i++) {
		if (blockComponents[0][i] < '0' || blockComponents[0][i]>'9')return false;
	}
	if (++idOfBlocks[blockComponents[0]] > 1)return false;
	Validator* blockValidator = createBlockValidator(blockComponents);
	if (num > 1 && dynamic_cast<ReadFileValidator*>(blockValidator) != nullptr)return false;
	if (num == data.size() && dynamic_cast<WriteFileValidator*>(blockValidator) != nullptr)return false;   // change first condition
	if (blockValidator == nullptr)return false;
	bool valid = blockValidator->isValid();
	delete blockValidator;
	return valid;
}

Validator* SchemeValidator::createBlockValidator(std::vector<std::string>& blockComponents)
{
	if (blockComponents[2] == "writefile")return new WriteFileValidator(blockComponents);
	if (blockComponents[2] == "readfile")return new ReadFileValidator(blockComponents);
	if (blockComponents[2] == "sort")return new SortValidator(blockComponents);
	if (blockComponents[2] == "dump")return new DumpValidator(blockComponents);
	if (blockComponents[2] == "replace")return new ReplaceValidator(blockComponents);
	if (blockComponents[2] == "grep")return new GrepValidator(blockComponents);
	return nullptr;
}


