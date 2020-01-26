#include "Shot.h"

Shot::Shot(int col, int row, ShotStatus type) : row(row), col(col), type(type)
{
}

Shot::Shot() : row(-1), col(-1), type(ShotStatus::Miss)
{
}

Shot::~Shot()
{
}

std::pair<int, int> Shot::getPos() const
{
	return { col,row };
}

ShotStatus Shot::getType() const
{
	return type;
}

void Shot::setType(ShotStatus type)
{
	this->type = type;
}



bool Shot::operator<(const Shot& other) const
{
	return this->getPos() < other.getPos();
}

