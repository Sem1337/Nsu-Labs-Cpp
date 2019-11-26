#pragma once
#include "GamePresenter.h"
class ConsoleGamePresenter :
	public GamePresenter
{
public:
	ConsoleGamePresenter(int width = 30, int height = 30);
	~ConsoleGamePresenter();
	virtual void showGameFrame(const std::vector<Ship>&, const std::vector<Ship>&,
		const std::vector<Shot>&, const std::vector<Shot>&) override;
private:
	ConsoleView window;
};

