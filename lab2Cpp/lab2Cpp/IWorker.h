#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <algorithm>
#include <iostream>
#include "ExecutionException.h"

enum class DataType {
	Void,
	Text
};

class IWorker
{
public:
	IWorker() {};
	virtual ~IWorker() {};
	virtual void execute() = 0;
	virtual DataType input() const = 0;
	virtual DataType output() const = 0;
private:
};

