#pragma once
#include <set>
#include <unordered_set>
#include "ConsoleView.h"
#include "ConsoleViewConstants.h"
#include <Windows.h>
#include "Shot.h"
#include <SFML/Graphics.hpp>

enum class PresenterType
{
	ConsolePresent,
	GraphicPresent
};


class GamePresenter
{
public:
	GamePresenter(int, int, PresenterType);
	~GamePresenter();
	void showGameFrame(const std::vector<Ship>&, const std::vector<Ship>&,
		const std::set<Shot>&, const std::set<Shot>&, const std::shared_ptr<Shot>&, const std::shared_ptr<Shot>&);
private:
	void cleanFrame();
	std::shared_ptr<GameView> addShotView(const Shot&, std::shared_ptr<GameView>);
	std::shared_ptr<GameView> addShipsView(const std::vector<Ship>&, int);
	std::shared_ptr<GameView> addFieldView(int, int);
	std::shared_ptr<GameView> addLastShotsInfoView(const std::shared_ptr<Shot>&, const std::shared_ptr<Shot>&);
	PresenterType type;
	std::shared_ptr<GameView> window;

};

