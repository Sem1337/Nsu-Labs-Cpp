#include "Game.h"

Game::Game(int roundsCount, int gamerType1, int gamerType2, PresenterType presenterType) : roundsCount(roundsCount)
{
	srand((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
	presenter = std::make_unique<GamePresenter>(WINDOW_WIDTH, WINDOW_HEIGHT, presenterType);

	switch (gamerType1)
	{
	case 1: gamer1 = std::make_unique<ConsoleGamer>(); break;
	case 2: gamer1 = std::make_unique<RandomGamer>(); break;
	case 3: gamer1 = std::make_unique<OptimalGamer>(); break;
	default:
		gamer1 = std::make_unique<ConsoleGamer>();
	}

	switch (gamerType2)
	{
	case 1: gamer2 = std::make_unique<ConsoleGamer>(); break;
	case 2: gamer2 = std::make_unique<RandomGamer>(); break;
	case 3: gamer2 = std::make_unique<OptimalGamer>(); break;
	default:
		gamer2 = std::make_unique<ConsoleGamer>();
	}
}

Game::~Game()
{
}

void Game::run()
{
	for (; roundsCount > 0; roundsCount--) {

		setup();

		int turn = 0;
		while (true) {
			presenter->showGameFrame(ships1, ships2, shots1, shots2,lastShot1,lastShot2);
			
			int winner = checkWinner();
			if (winner)break;

			askShot(turn);

		
		}

		if (!endRound())break;
	}
}




void Game::setup()
{
	askShips(0);
	askShips(1);
}

void Game::askShips(int turn)
{
	Gamer& gamer = (turn == 0 ? *gamer1 : *gamer2);
	std::vector<Ship>& ships = (turn == 0 ? ships1 : ships2);

	for (int count = 1; count <= 4; count++) {
		for (int placed = 0; placed < count; ) {
			std::cout << "place " << 5 - count << " size ship\n"; // change to presenter::askShipPosition()
			try {
				Ship newShip = Parser::parseShip(gamer.placeShip());
				if (newShip.getLength() != 5 - count) {
					throw std::exception("incorrect ship size");
				}
				for (auto ship : ships) {
					if (ship.intersect(newShip))throw std::exception("ships intersection");
				}
				ships.push_back(newShip);
				placed++;
			}
			catch (const std::exception & e) {
				std::cout << e.what() << std::endl; // change to presenter::showShipError()
			}
		}
	}
}

void Game::askShot(int &turn)
{
	int correctShoot = 0;
	Gamer& gamer = (turn == 0 ? *gamer1 : *gamer2);
	std::set<Shot>& shots = (turn == 0 ? shots1 : shots2);
	while (!correctShoot) {
		try {
			std::pair<int, int> cell = Parser::parseShot(gamer.shoot());
			correctShoot = 1;
			Shot newShot = handleCell(cell, turn);
			if (turn == 0) {
				lastShot1 = std::make_shared<Shot>(newShot);
			}
			else {
				lastShot2 = std::make_shared<Shot>(newShot);
			}
			if (newShot.getType() == ShotStatus::Miss)turn ^= 1;
			shots.insert(newShot);
			
			gamer.setLastSuccessfulShot(newShot);
		}
		catch (const std::exception & e) {
			std::cout << e.what() << std::endl;
		}
	}
}

Shot Game::handleCell(std::pair<int, int> cell, int turn)
{
	std::set<Shot>& shots = (turn == 0) ? shots1 : shots2;
	std::vector<Ship>& ships = (turn == 0 ? ships2 : ships1);
	for (auto& ship : ships) {
		for (int col = ship.getFirstSide().first; col <= ship.getSecondSide().first; col++) {
			for (int row = ship.getFirstSide().second; row <= ship.getSecondSide().second; row++) {
				if (cell == std::make_pair(col, row)) {
					Shot newShot = Shot(cell.first, cell.second, ShotStatus::Hit);
					if (shots.find(newShot) == shots.end()) {
						ship.hit();
						if (ship.getHP() == 0) {
							newShot.setType(ShotStatus::Destroy);
						}
					}
					return newShot;
				}
			}
		}
	}
	return Shot(cell.first, cell.second, ShotStatus::Miss);
}

bool Game::endRound()
{
	ships1.clear();
	ships2.clear();
	shots1.clear();
	shots2.clear();
	lastShot1 = nullptr;
	lastShot2 = nullptr;
	gamer1->reset();
	gamer2->reset();
	return gamer1->ready() && gamer2->ready();
}

int Game::checkWinner()
{
	int alive = 0;
	for (auto ship : ships1) {
		if (ship.getHP() > 0)alive = 1;
	}
	if (!alive) {
		std::cout << "Gamer 2 win\n";
		return 2;
	}
	alive = 0;
	for (auto ship : ships2) {
		if (ship.getHP() > 0)alive = 1;
	}
	if (!alive) {
		std::cout << "Gamer 1 win\n";
		return 1;
	}
	return 0;
}
