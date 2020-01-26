#pragma once
#include "Gamer.h"
class RandomGamer :
	public Gamer
{
public:
	RandomGamer();
	~RandomGamer();
	virtual std::string shoot() override;
	virtual std::string placeShip() override;
	virtual void setLastSuccessfulShot(Shot) override;
	virtual bool ready() override;
	virtual void reset() override;
private:
	void makeShipsPlacement();
	void putHorizontally(int size);
	void putVertically(int size);
	std::vector<std::vector<char>>field;
	std::vector<std::string>shipsPlacement;
	std::vector<std::string>shotsOrder;
	int currentShot;
	int currentShip;

};

