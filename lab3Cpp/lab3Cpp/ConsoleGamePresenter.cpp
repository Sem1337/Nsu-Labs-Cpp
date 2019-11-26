#include "ConsoleGamePresenter.h"

ConsoleGamePresenter::ConsoleGamePresenter(int width, int height) : window(width,height,0,0,' ')
{
}

ConsoleGamePresenter::~ConsoleGamePresenter()
{
}

void ConsoleGamePresenter::showGameFrame(const std::vector<Ship>& ships1, const std::vector<Ship>& ships2, const std::vector<Shot>& shots1, const std::vector<Shot>& shots2)
{
	ConsoleView field1(10, 10, 2, 2);
	ConsoleView field2(10, 10, 15, 2);
	for (auto shot : shots1) {
		char shotType = shot.getType() == 0 ? '0' : '1';
		field1.addSubview(std::make_shared<ConsoleView>(1, 1, shot.getPos().first - 1, shot.getPos().second - 1, shotType));
	}
	for (auto shot : shots2) {
		char shotType = shot.getType() == 0 ? '0' : '1';
		field2.addSubview(std::make_shared<ConsoleView>(1, 1, shot.getPos().first - 1, shot.getPos().second - 1, shotType));
	}
	window.addSubview(std::make_shared<ConsoleView>(field1));
	window.addSubview(std::make_shared<ConsoleView>(field2));
	// add remaining ships
	window.show();
	field1.remove();
	field2.remove();
}
