#pragma once
#include <conio.h>
#include <map>
#include <set>
#include <random>
#include <chrono>
#include <Windows.h>
#include "ConsoleGamer.h"
#include "GamePresenter.h"
#include "RandomGamer.h"
#include "OptimalGamer.h"
#include "ConsoleViewConstants.h"
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
	void askShot(int&);
	Shot handleCell(std::pair<int, int>, int);
	bool endRound();
	int roundsCount;
	std::unique_ptr<Gamer> gamer1;
	std::unique_ptr<Gamer> gamer2;
	std::vector<Ship>ships1;
	std::vector<Ship>ships2;
	std::set<Shot>shots1;
	std::set<Shot>shots2;
	std::shared_ptr<Shot>lastShot1;
	std::shared_ptr<Shot>lastShot2;
	std::unique_ptr<GamePresenter> presenter;
};

