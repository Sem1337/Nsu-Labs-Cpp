#include "Ship.h"


Ship::Ship(const Ship& ship)
{
	hp = ship.hp;

	firstSide = ship.firstSide;
	secondSide = ship.secondSide;
	if (std::min(abs(firstSide.first - secondSide.first), abs(firstSide.second - secondSide.second)) != 0) {
		throw std::exception("incorrect ship size");
	}

}

Ship::Ship(std::pair<int, int> firstSide, std::pair<int, int> secondSide)
{
	if (firstSide.first > secondSide.first)swap(firstSide, secondSide);
	else if (firstSide.second > secondSide.second)swap(firstSide, secondSide);
	this->firstSide = firstSide;
	this->secondSide = secondSide;
	hp = getLength();
}

Ship::~Ship()
{
}


int Ship::getLength() const
{
	return std::max(abs(firstSide.first - secondSide.first), abs(firstSide.second - secondSide.second)) + 1;
}

std::pair<int, int> Ship::getFirstSide() const
{
	return firstSide;
}

std::pair<int, int> Ship::getSecondSide() const
{
	return secondSide;
}

bool Ship::intersect(Ship ship)
{
	for (int col1 = firstSide.first - 1; col1 <= secondSide.first + 1; col1++) {
		for (int row1 = firstSide.second - 1; row1 <= secondSide.second + 1; row1++) {
			for (int col2 = ship.firstSide.first; col2 <= ship.secondSide.first; col2++) {
				for (int row2 = ship.firstSide.second; row2 <= ship.secondSide.second; row2++) {
					if (col1 == col2 && row1 == row2)return true;
				}
			}
		}
	}
	return false;
}

int Ship::getHP() const
{
	return hp;
}

void Ship::hit()
{
	hp--;
}
