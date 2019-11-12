#pragma once
#include <vector>
#include <strstream>
#include <sstream>
#include <string>
#include <map>
#include "ValidationException.h"
#include "StrExtd.h"

class Validator
{
public:
	Validator() {};
	virtual ~Validator() {};
	virtual void validation() = 0;
private:

};

