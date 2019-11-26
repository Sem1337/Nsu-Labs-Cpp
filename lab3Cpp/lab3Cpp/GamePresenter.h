#pragma once
#include "ConsoleView.h"
#include "Shot.h"
class GamePresenter
{
public:
	GamePresenter() {};
	~GamePresenter() {};
	virtual void showGameFrame(const std::vector<Ship>&, const std::vector<Ship>&,
		const std::vector<Shot>&, const std::vector<Shot>&) = 0;
private:

};

