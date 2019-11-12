#pragma once
#include <exception>
#include <iostream>
#include "ValidationException.h"
#include "ParsingException.h"
#include "ExecutionException.h"
#include "ReadFile.h"
#include "SchemeValidator.h"
#include "SchemeParser.h"
#include "Scheme.h"
#include "Sort.h"
#include "Replace.h"
#include "ReadFile.h"
#include "WriteFile.h"
#include "Dump.h"
#include "Grep.h"
class Workflow             
{						  
public:					 
	Workflow(const std::string& fileName ,const std::string& in = "",const std::string& out= "");
	~Workflow();
private:					
	std::vector<std::string>data;                 
};


