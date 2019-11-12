#pragma once
#include "WriteFileValidator.h"
#include "ValidationException.h"
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
	virtual void validation() override;
private:
	const std::vector<std::string>& data;
	void blockValidation(const std::string&, int);
	std::unique_ptr<Validator> createBlockValidator(std::vector<std::string>&);
	std::map<std::string, int>idOfBlocks;
};

