#include "GamePresenter.h"

GamePresenter::GamePresenter(int width, int height, PresenterType type) : type(type)
{
	std::cout.sync_with_stdio(false);
	std::cout.tie(false);
	switch (type) {
	case PresenterType::ConsolePresent: window = std::make_shared<ConsoleView>(width, height, 0, 0, ' ');
	default: window = std::make_shared<ConsoleView>(width, height, 0, 0, ' ');
	}
}

GamePresenter::~GamePresenter()
{
}

void GamePresenter::showGameFrame(const std::vector<Ship>& ships1, const std::vector<Ship>& ships2, const std::set<Shot>& shots1,
	const std::set<Shot>& shots2, const std::shared_ptr<Shot>& lastShot1, const std::shared_ptr<Shot>& lastShot2)
{
	Sleep(50);
	cleanFrame();
	std::shared_ptr<GameView>gamer1Label(new ConsoleView(6, 1, GAMER1_FIELD_LEFT_ANCHOR + 4, GAMER1_FIELD_TOP_ANCHOR - 2, ' ', "gamer1"));
	std::shared_ptr<GameView>gamer2Label(new ConsoleView(6, 1, GAMER2_FIELD_LEFT_ANCHOR + 4, GAMER2_FIELD_TOP_ANCHOR - 2, ' ', "gamer2"));
	window->addSubview(gamer1Label);
	window->addSubview(gamer2Label);
	std::shared_ptr<GameView>field1 = addFieldView(GAMER1_FIELD_LEFT_ANCHOR, GAMER1_FIELD_TOP_ANCHOR);
	std::shared_ptr<GameView>field2 = addFieldView(GAMER2_FIELD_LEFT_ANCHOR, GAMER2_FIELD_TOP_ANCHOR);
	for (auto shot : shots1) {
		field1->addSubview(addShotView(shot, field1));
	}
	for (auto shot : shots2) {
		field2->addSubview(addShotView(shot, field2));
	}
	window->addSubview(field1);
	window->addSubview(field2);

	std::shared_ptr<GameView>infoBar = addLastShotsInfoView(lastShot1, lastShot2);
	window->addSubview(infoBar);
	window->addSubview(addShipsView(ships1, 2));
	window->addSubview(addShipsView(ships2, 1));

	// add remaining ships
	window->show();
	infoBar->removeFromSuperView();
	field1->removeFromSuperView();
	field2->removeFromSuperView();
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
		char shotImage = (shot.getType() == ShotStatus::Miss ? MISS_CELL : DAMAGED_CELL);
		return std::make_shared<ConsoleView>(FIELD_CELL_WIDTH, FIELD_CELL_HEIGHT, (shot.getPos().first - 1) * FIELD_CELL_WIDTH + 2, (shot.getPos().second - 1) * FIELD_CELL_HEIGHT + 1, shotImage);
	}
	return nullptr;
}

std::shared_ptr<GameView> GamePresenter::addShipsView(const std::vector<Ship>& ships, int gamer)
{
	int left = gamer == 1 ? REMAINING_SHIPS1_LEFT_ANCHOR : REMAINING_SHIPS2_LEFT_ANCHOR;
	switch (type)
	{
	case PresenterType::ConsolePresent:
		std::shared_ptr<ConsoleView>remainingShips = std::make_shared<ConsoleView>(REMAINING_SHIPS_WIDTH, REMAINING_SHIPS_HEIGHT, left, REMAINING_SHIPS_TOP_ANCHOR, ' ',REMAINING_SHIPS_LABEL);
		int shift = 1;
		for (auto ship : ships) {
			if (ship.getHP() > 0) {
				remainingShips->addSubview(std::make_shared<ConsoleView>(ship.getLength() * FIELD_CELL_WIDTH, FIELD_CELL_HEIGHT, 0, shift, DAMAGED_CELL));
				shift += FIELD_CELL_HEIGHT + 1;
			}
		}
		return remainingShips;
	}
	return nullptr;
}

std::shared_ptr<GameView> GamePresenter::addFieldView(int leftAnchor, int topAnchor)
{
	std::shared_ptr<ConsoleView>field;
	switch (type)
	{
	case PresenterType::ConsolePresent:
		field = std::make_shared<ConsoleView>(FIELD_WIDTH, FIELD_HEIGHT, leftAnchor, topAnchor, ' ');
		field->addSubview(std::make_shared<ConsoleView>(FIELD_CELL_WIDTH * 10, FIELD_CELL_HEIGHT * 10, 2, 1, UNCHECKED_CELL));
		for (char col = 0; col < 10; col++) {
			field->addSubview(std::make_shared<ConsoleView>(1, 1, 2 + col * FIELD_CELL_WIDTH + FIELD_CELL_WIDTH / 2, 0, col + 'a'));
		}
		for (char row = 0; row < 9; row++) {
			field->addSubview(std::make_shared<ConsoleView>(1, 1, 1, 1 + row * FIELD_CELL_HEIGHT + FIELD_CELL_HEIGHT / 2, row + '1'));
		}
		field->addSubview(std::make_shared<ConsoleView>(2, 1, 0, 1 + 9 * FIELD_CELL_HEIGHT + FIELD_CELL_HEIGHT / 2, ' ', "10"));
		return field;
	}
	return nullptr;
}

std::shared_ptr<GameView> GamePresenter::addLastShotsInfoView(const std::shared_ptr<Shot>& shot1, const std::shared_ptr<Shot>& shot2)
{
	std::shared_ptr<ConsoleView>infoBar(std::make_shared<ConsoleView>(INFO_BAR_WIDTH, INFO_BAR_HEIGHT, INFO_BAR_LEFT_ANCHOR, INFO_BAR_TOP_ANCHOR));
	infoBar->addSubview(std::make_shared<ConsoleView>(INFO_BAR_LAST_SHOT1_LABEL.length(), 1, INFO_BAR_LAST_SHOT1_LEFT_ANCHOR, 0, ' ', INFO_BAR_LAST_SHOT1_LABEL));
	if (shot1.get() != nullptr) {
		char col = shot1->getPos().first - 1 + 'a';
		std::string shotToString = std::string{ col }+" " + std::to_string(shot1->getPos().second) + " ";
		if (shot1->getType() == ShotStatus::Miss) {
			shotToString += "Miss";
		}
		if (shot1->getType() == ShotStatus::Hit) {
			shotToString += "Hit";
		}
		if (shot1->getType() == ShotStatus::Destroy) {
			shotToString += "Destroyed!";
		}
		infoBar->addSubview(std::make_shared<ConsoleView>(shotToString.length(), 1, INFO_BAR_LAST_SHOT1_LEFT_ANCHOR, 3, ' ', shotToString));
	}
	infoBar->addSubview(std::make_shared<ConsoleView>(INFO_BAR_LAST_SHOT2_LABEL.length(), 1, INFO_BAR_LAST_SHOT2_LEFT_ANCHOR, 0, ' ', INFO_BAR_LAST_SHOT2_LABEL));
	if (shot2.get() != nullptr) {
		char col = shot2->getPos().first - 1 + 'a';
		std::string shotToString = std::string{ col }+" " + std::to_string(shot2->getPos().second) + " ";
		if (shot2->getType() == ShotStatus::Miss) {
			shotToString += "Miss";
		}
		if (shot2->getType() == ShotStatus::Hit) {
			shotToString += "Hit";
		}
		if (shot2->getType() == ShotStatus::Destroy) {
			shotToString += "Destroyed!";
		}
		infoBar->addSubview(std::make_shared<ConsoleView>(shotToString.length(), 1, INFO_BAR_LAST_SHOT2_LEFT_ANCHOR, 3, ' ', shotToString));

	}
	return infoBar;
}

