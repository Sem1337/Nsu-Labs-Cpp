#pragma once
#include <vector>
#include <algorithm>
class Ship
{
public:
	Ship(const Ship&);
	Ship(std::pair<int, int>, std::pair<int, int>);
	~Ship();
	int getLength() const;
	std::pair<int, int> getFirstSide() const;
	std::pair<int, int> getSecondSide() const;
	bool intersect(Ship);
	int getHP() const;
	void hit();
private:
	int hp;
	std::pair<int, int>firstSide;
	std::pair<int, int>secondSide;
};

