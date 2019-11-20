#pragma once
#include "GameView.h"
class ConsoleView :
	public GameView
{
public:

	ConsoleView();
	~ConsoleView();
	virtual void show();
	virtual void addSubview(std::shared_ptr<GameView>) override;

private:
	
	std::vector<std::vector<char>>background;
	std::list<std::shared_ptr<GameView>>subViews;

	int width = 30;
	int height = 30;
	int leftAnchor = 0;
	int topAnchor = 0;

};

