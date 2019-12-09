/*#pragma once
#include "GameView.h"
#include <SFML/Graphics.hpp>
class GraphicView :
	public GameView
{
public:
	GraphicView(int w, int h, int l, int t, sf::Color);
	~GraphicView();
	virtual void show() override;
	virtual void addSubview(std::shared_ptr<GameView>) override;
	virtual void removeFromSuperView() override;
	virtual void setSuperView(std::shared_ptr<GameView>) override;
	virtual std::list<std::shared_ptr<GameView>>& getSubviews() override;
	virtual void setLeftAnchor(int) override;
	virtual void setTopAnchor(int) override;
	void resize(int width, int height) override;

private:
	sf::Sprite sprite;

	std::list<std::shared_ptr<GameView>>subViews;
	std::weak_ptr<GameView> superView;
};
*/
