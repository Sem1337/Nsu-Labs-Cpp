#pragma once

#include <vector>
#include <string>
#include <memory>
#include <stack>
#include <list>
#include <algorithm>
#include <vector>
#include "Ship.h"
class GameView
{
public:

	GameView() {};
	virtual ~GameView() {};
	virtual void show() = 0;
	virtual void addSubview(std::shared_ptr<GameView>) = 0;
	virtual void remove() = 0;
	virtual std::list<std::shared_ptr<GameView>>& getSubviews() = 0;
	virtual void resize(int, int) = 0;
	virtual void setLeftAnchor(int) = 0;
	virtual void setTopAnchor(int) = 0;

private:
};

