#pragma once

#include <vector>
#include <string>
#include <memory>
#include <stack>
#include <list>

class GameView
{
public:

	GameView() {};
	virtual ~GameView() {};
	virtual void show() const = 0;
	virtual void addSubview(std::shared_ptr<GameView>) = 0;
	virtual void setWidth() = 0;
	virtual void setHeight() = 0;
	virtual void setLeftAnchor() = 0;
	virtual void setTopAnchor() = 0;

private:
	
};

