#pragma once
#include "ConsoleView.h"
#include "Shot.h"

enum class PresenterType
{
	ConsolePresent
};


class GamePresenter
{
public:
	GamePresenter(int, int, PresenterType);
	~GamePresenter();
	void showGameFrame(const std::vector<Ship>&, const std::vector<Ship>&,
		const std::vector<Shot>&, const std::vector<Shot>&);
private:
	void cleanFrame();
	std::shared_ptr<GameView> addShotView(const Shot&, std::shared_ptr<GameView>);
	std::shared_ptr<GameView> addShipView(const Ship&, std::shared_ptr<GameView>);
	std::shared_ptr<GameView> addFieldView(int, int);
	PresenterType type;
	std::shared_ptr<GameView> window;

};

