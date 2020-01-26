#pragma once
#include "GameView.h"
#include <iostream>
class ConsoleView :
	public GameView
{
public:

	ConsoleView();
	ConsoleView(int w, int h, int l, int t, char backgroundSym = ' ', std::string text = "");
	~ConsoleView();
	virtual void show() override;
	virtual void addSubview(std::shared_ptr<GameView>) override;
	virtual void removeFromSuperView() override;
	virtual void setSuperView(std::shared_ptr<GameView>) override;
	virtual std::list<std::shared_ptr<GameView>>& getSubviews() override;
	virtual void setLeftAnchor(int) override;
	virtual void setTopAnchor(int) override;
	void resize(int width, int height) override;
	const std::vector<std::vector<char>>& getContent() const;


private:

	std::vector<std::vector<char>>content;
	std::vector<std::vector<char>>background;
	std::list<std::shared_ptr<GameView>>subViews;
	std::weak_ptr<GameView> superView;

	int width = 30;
	int height = 30;
	//in superview coordinates
	int leftAnchor = 0;
	int topAnchor = 0;

};

