#include "SchemeValidator.h"

SchemeValidator::SchemeValidator(const std::vector<std::string>& data) : data(data)
{
}

SchemeValidator::~SchemeValidator()
{
}

void SchemeValidator::validation()
{
	if (data.size() < 2)throw ValidationException("Incorrect scheme format");
	if (data[0] != "desc")throw ValidationException("'desc' not found");                //desc doesn't exist
	int currentString = 1;
	int countOfStr = data.size();
	while (currentString < countOfStr && data[currentString] != "csed") {
		blockValidation(data[currentString], currentString);
		currentString++;
	}
	if (currentString == countOfStr)throw ValidationException("'csed' not found");    // csed doesn't exist
	if (++currentString == countOfStr)return;
	std::vector<std::string> sequenceComponents = StrExtd::tokenize(data[currentString]);
	for (size_t i = 0; i < sequenceComponents.size(); i++) {
		if (i & 1) {
			if (sequenceComponents[i] != "->")throw ValidationException("Incorrect sequence format");
		}
		else {
			if (idOfBlocks.find(sequenceComponents[i]) == idOfBlocks.end())throw ValidationException("Undeclared block found in the sequence");
		}
	}
	
	if (++currentString == countOfStr)return;
	throw ValidationException("bad data found");
}

void SchemeValidator::blockValidation(const std::string& block, int num)
{
	std::vector<std::string> blockComponents = StrExtd::tokenize(block);
	if (blockComponents.size() < 3)throw ValidationException("Incorrect block format");
	for (size_t i = 0; i < blockComponents[0].length(); i++) {
		if (blockComponents[0][i] < '0' || blockComponents[0][i]>'9')throw ValidationException("Incorrect id");
	}
	if (blockComponents[1] != "=")throw ValidationException("Incorrect format after id");
	if (++idOfBlocks[blockComponents[0]] > 1)throw ValidationException("More than 1  id definitions");
	std::unique_ptr<Validator> blockValidator = createBlockValidator(blockComponents);
	if (blockValidator == nullptr)throw ValidationException("Incorrect block name");
	blockValidator->validation();
}

std::unique_ptr<Validator> SchemeValidator::createBlockValidator(std::vector<std::string>& blockComponents)
{
	if (blockComponents[2] == "writefile")return std::unique_ptr<Validator>(new WriteFileValidator(blockComponents));
	if (blockComponents[2] == "readfile")return std::unique_ptr<Validator>(new ReadFileValidator(blockComponents));
	if (blockComponents[2] == "sort")return std::unique_ptr<Validator>(new SortValidator(blockComponents));
	if (blockComponents[2] == "dump")return std::unique_ptr<Validator>(new DumpValidator(blockComponents));
	if (blockComponents[2] == "replace")return std::unique_ptr<Validator>(new ReplaceValidator(blockComponents));
	if (blockComponents[2] == "grep")return std::unique_ptr<Validator>(new GrepValidator(blockComponents));
	return nullptr;
}


