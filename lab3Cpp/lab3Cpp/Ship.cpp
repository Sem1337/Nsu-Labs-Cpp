#include "Ship.h"


Ship::Ship(const Ship& ship)
{
	hp = ship.hp;

	firstSide = ship.firstSide;
	secondSide = ship.secondSide;
}

Ship::Ship(std::pair<int, int> firstSide, std::pair<int, int> secondSide)
{
	if (firstSide.first > secondSide.first)swap(firstSide, secondSide);
	else if (firstSide.second > secondSide.second)swap(firstSide, secondSide);
	this->firstSide = firstSide;
	this->secondSide = secondSide;
	hp = getWidth() * getLength();
}

Ship::~Ship()
{
}

int Ship::getWidth() const
{
	return std::min(abs(firstSide.first - secondSide.first), abs(firstSide.second - secondSide.second));
}

int Ship::getLength() const
{
	return std::max(abs(firstSide.first - secondSide.first), abs(firstSide.second - secondSide.second));
}

std::pair<int, int> Ship::getFirstSide() const
{
	return firstSide;
}

std::pair<int, int> Ship::getSecondSide() const
{
	return secondSide;
}

int Ship::getHP() const
{
	return hp;
}

void Ship::hit()
{
	hp--;
}
