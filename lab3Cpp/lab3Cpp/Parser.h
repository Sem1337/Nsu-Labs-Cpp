#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <exception>
#include "Ship.h"
#include "Shot.h"
class Parser
{
public:
	static std::pair<int,int> parseShot(std::string);
	static Ship parseShip(std::string);
	static std::vector<std::string> tokenize(const std::string& input, char separator = ' ');
private:

};

