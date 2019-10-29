#pragma once
#include "Validator.h"
#include "WriteFileValidator.h"
#include "ReadFileValidator.h"
#include "ReplaceValidator.h"
#include "SortValidator.h"
#include "GrepValidator.h"
#include "DumpValidator.h"
class SchemeValidator :
	public Validator
{
public:
	SchemeValidator(const std::vector<std::string> &  data);
	virtual ~SchemeValidator();
	virtual bool isValid() override;
private:
	const std::vector<std::string>& data;
	bool isValidBlock(const std::string&, int);
	Validator* createBlockValidator(std::vector<std::string>&);
	std::map<std::string, int>idOfBlocks;
};

