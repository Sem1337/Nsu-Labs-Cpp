#include "Shot.h"

Shot::Shot(int col, int row, int type) : row(row), col(col), type(type)
{
}

Shot::~Shot()
{
}

std::pair<int, int> Shot::getPos() const
{
	return { col,row };
}

int Shot::getType() const
{
	return type;
}
