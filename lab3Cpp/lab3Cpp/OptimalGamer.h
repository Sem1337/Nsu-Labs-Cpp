#pragma once
#include "Gamer.h"

enum class State {
	search,
	tryUpSide,
	tryDownSide,
	tryLeftSide,
	tryRightSide
};

class OptimalGamer :
	public Gamer
{
public:
	OptimalGamer();
	~OptimalGamer();
	virtual std::string shoot() override;
	virtual std::string placeShip() override;
	virtual void setLastSuccessfulShot(Shot) override;
	virtual bool ready() override;
	virtual void reset() override;
private:
	void makeOptimalShipsPlacement();
	void placeVerticalShipOnShipsField(char col, int row, int size);
	std::pair<char, int> findAvailablePlace();
	void updateFoundArea(std::pair<int,int>);
	void removeUselessShots();
	void nextState();
	void resetFoundArea();
	bool isValidState();
	
	State state;
	
	std::vector<std::vector<char>>shotsField;
	std::vector<std::vector<char>>shipsField;
	
	std::vector<std::string>shipsPlacement;
	std::vector<std::string>shotsOrder;
	
	Shot lastShot;
	
	int currentShot;
	int currentShip;

	int foundLeftSide;
	int foundRightSide;
	int foundUpSide;
	int foundDownSide;

};

