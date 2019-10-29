#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <list>

class IWorker
{
public:
	IWorker() {};
	virtual ~IWorker() {};
	virtual void execute() = 0;
private:
};

