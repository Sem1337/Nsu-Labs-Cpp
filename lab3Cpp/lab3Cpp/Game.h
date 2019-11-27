#pragma once
#include "ConsoleGamer.h"
#include "GamePresenter.h"
#include "Parser.h"
#include "Ship.h"
class Game
{
public:
	Game(int, int, int, PresenterType);
	~Game();
	void run();
private:
	void setup();
	int checkWinner();
	void askShips(int);
	void askShot(int);
	Shot handleCell(std::pair<int, int>, int);
	void endRound();
	int roundsCount;
	std::unique_ptr<Gamer> gamer1;
	std::unique_ptr<Gamer> gamer2;
	std::vector<Ship>ships1;
	std::vector<Ship>ships2;
	std::vector<Shot>shots1;
	std::vector<Shot>shots2;
	std::unique_ptr<GamePresenter> presenter;
};

