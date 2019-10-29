#pragma once
#include <vector>
#include <strstream>
#include <sstream>
#include <string>
#include <map>
#include "StrExtd.h"

class Validator
{
public:
	Validator() {};
	virtual ~Validator() {};
	virtual bool isValid() = 0;
private:

};

