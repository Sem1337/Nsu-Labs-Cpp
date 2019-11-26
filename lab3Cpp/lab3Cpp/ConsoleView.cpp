#include "ConsoleView.h"

ConsoleView::ConsoleView(): superView(nullptr)
{
	content.assign(height, std::vector<char>(width));
	background.assign(height, std::vector<char>(width, ' '));
}

ConsoleView::ConsoleView(int width, int height, int leftAnchor,int topAnchor,char backgroundSym, std::shared_ptr<ConsoleView> superView)
	: width(width), height(height), topAnchor(topAnchor),leftAnchor(leftAnchor), superView(superView)
{
	content.assign(height, std::vector<char>(width));
	background.assign(height, std::vector<char>(width, backgroundSym));
}



ConsoleView::~ConsoleView()
{
}

void ConsoleView::show()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			content[i][j] = background[i][j];
		}
	}

	for (auto &view : subViews) {
		view->show();
		ConsoleView* subView = dynamic_cast<ConsoleView*>(view.get());
		if (!subView)continue;
		const std::vector<std::vector<char>>& subViewContent = subView->getContent();
		for (int i = subView->topAnchor; i < subView->topAnchor + subView->height; i++) {
			for (int j = subView->leftAnchor; j < subView->leftAnchor + subView->width; j++) {
				content[i][j] = subViewContent[i - subView->topAnchor][j - subView->leftAnchor];
			}
		}
	}
	if (superView == nullptr) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				std::cout << content[i][j];
			}
			std::cout << std::endl;
		}
	}
}

void ConsoleView::addSubview(std::shared_ptr<GameView> subView)
{

	subViews.push_back(subView);
}

void ConsoleView::remove()
{
	for (auto view : superView.get()->getSubviews()) {
		if (view.get() == this) {
			superView.get()->getSubviews().remove(view);
			return;
		}
	}
}

std::list<std::shared_ptr<GameView>>& ConsoleView::getSubviews()
{
	return subViews;
}


void ConsoleView::setLeftAnchor(int leftAnchor)
{
	this->leftAnchor = leftAnchor;
}

void ConsoleView::setTopAnchor(int topAnchor)
{
	this->topAnchor = topAnchor;
}

const std::vector<std::vector<char>>& ConsoleView::getContent() const
{
	return content;
}

void ConsoleView::resize(int width, int height)
{
	std::vector<std::vector<char>>oldViewBackground = background;
	background.resize(height, std::vector<char>(width));
	for (int i = 0; i < std::min(this->height, height); i++) {
		for (int j = 0; j < std::min(this->width, width); j++) {
			background[i][j] = oldViewBackground[i][j];
		}
	}
	this->width = width;
	this->height = height;
}
