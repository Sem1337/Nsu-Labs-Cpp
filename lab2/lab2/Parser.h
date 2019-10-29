#pragma once
#include <vector>
#include <string>
#include <map>
#include <list>
#include "StrExtd.h"
class Parser
{
public:
	Parser() {};
	virtual ~Parser() {};
	virtual void parse() = 0;
private:

};

