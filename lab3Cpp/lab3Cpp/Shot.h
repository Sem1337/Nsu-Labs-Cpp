#pragma once
#include <vector>

enum class ShotStatus {
	Miss,
	Hit,
	Destroy
};

class Shot
{
public:
	Shot(int, int, ShotStatus);
	Shot();
	~Shot();
	std::pair<int, int> getPos() const;
	ShotStatus getType() const;
	void setType(ShotStatus);
	bool operator<(const Shot&) const;
private:
	int row;
	int col;
	ShotStatus type;
};

