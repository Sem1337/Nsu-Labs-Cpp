#pragma once
#include "Gamer.h"
class ConsoleGamer :
	public Gamer
{
public:
	ConsoleGamer();
	~ConsoleGamer();
	virtual std::string shoot() override;
	virtual std::string placeShip() override;
private:

};

