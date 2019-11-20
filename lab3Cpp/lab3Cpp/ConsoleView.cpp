#include "ConsoleView.h"

ConsoleView::ConsoleView()
{
	background.assign(height, std::vector<char>(width));
}

ConsoleView::~ConsoleView()
{
}

void ConsoleView::show()
{
	for (auto &view : subViews) {
		
	}
}

void ConsoleView::addSubview(std::shared_ptr<GameView> subView)
{
	subViews.push_back(subView);
}
