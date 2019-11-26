#pragma once
#include <memory>
#include <string>
#include <iostream>
class Gamer
{
public:

	Gamer() {};
	virtual ~Gamer() {};
	virtual std::string shoot() = 0;
	virtual std::string placeShip() = 0;
	
private:

};

