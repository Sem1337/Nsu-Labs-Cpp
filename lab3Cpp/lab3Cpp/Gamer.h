#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <Windows.h>
#include "Parser.h"
class Gamer
{
public:

	Gamer() {};
	virtual ~Gamer() {};
	virtual std::string shoot() = 0;
	virtual std::string placeShip() = 0;
	virtual void setLastSuccessfulShot(Shot) = 0;
	virtual bool ready() = 0;
	virtual void reset() = 0;
	
private:

};

