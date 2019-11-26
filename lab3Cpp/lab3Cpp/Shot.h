#pragma once
#include <vector>
class Shot
{
public:
	Shot(int, int, int);
	~Shot();
	std::pair<int, int> getPos() const;
	int getType() const;
	
private:
	int row;
	int col;
	int type;
};

