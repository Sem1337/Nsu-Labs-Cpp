#include "GamePresenter.h"

GamePresenter::GamePresenter(int width, int height, PresenterType type) : type(type)
{
	switch (type) {
	case PresenterType::ConsolePresent: window = std::make_shared<ConsoleView>(width, height, 0, 0, ' ');
	default: window = std::make_shared<ConsoleView>(width, height, 0, 0, ' ');
	}
}

GamePresenter::~GamePresenter()
{
}

void GamePresenter::showGameFrame(const std::vector<Ship>& ships1, const std::vector<Ship>& ships2, const std::vector<Shot>& shots1, const std::vector<Shot>& shots2)
{
	cleanFrame();
	std::shared_ptr<GameView>field1 = addFieldView(2, 3);
	std::shared_ptr<GameView>field2 = addFieldView(18, 3);
	for (auto shot : shots1) {
		field1->addSubview(addShotView(shot, field1));
	}
	for (auto shot : shots2) {
		field2->addSubview(addShotView(shot, field2));
	}
	window->addSubview(field1);
	window->addSubview(field2);
	// add remaining ships
	window->show();
	field1->remove();
	field2->remove();
}

void GamePresenter::cleanFrame()
{
	switch (type)
	{
	case PresenterType::ConsolePresent:
		system("cls");
	default:
		break;
	}
}

std::shared_ptr<GameView> GamePresenter::addShotView(const Shot& shot, std::shared_ptr<GameView> superView)
{
	switch (type)
	{
	case PresenterType::ConsolePresent:
		char shotImage = (shot.getType() == 0 ? '0' : '1');
		return std::make_shared<ConsoleView>(1, 1, shot.getPos().first, shot.getPos().second, shotImage, superView);
	}
}

std::shared_ptr<GameView> GamePresenter::addShipView(const Ship& ship, std::shared_ptr<GameView> superView)
{
	switch (type)
	{
	case PresenterType::ConsolePresent:
		return std::make_shared<ConsoleView>(ship.getLength(), ship.getWidth(), 0, 3, '$', superView);
	default:
		return nullptr;
	}
}

std::shared_ptr<GameView> GamePresenter::addFieldView(int leftAnchor,int topAnchor)
{
	switch (type)
	{
	case PresenterType::ConsolePresent:
		return std::make_shared<ConsoleView>(11, 11, leftAnchor, topAnchor, 219, window);
	default:
		nullptr;
	}
}

