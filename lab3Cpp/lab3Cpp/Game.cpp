#include "Game.h"

Game::Game(int roundsCount, int gamerType1, int gamerType2) : roundsCount(roundsCount)
{
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

			askShot(turn);

			int winner = checkWinner();
			if (winner == 1) {

			}
			else if (winner == 2) {

			}
			turn ^= 1;
		}

		endRound();
	}
}




void Game::setup()
{
	askShips(1);
	askShips(2);
}

void Game::askShips(int turn)
{
	Gamer& gamer = (turn == 0 ? *gamer1.get() : *gamer2.get());
	std::vector<Ship>& ships = (turn == 0 ? ships1 : ships2);

	for (int count = 1; count <= 4; count++) {
		for (int placed = 0; placed < count; ) {
			std::cout << "place " << 5 - count << " size ship\n"; // change to presenter::askShipPosition()
			try {
				Ship newShip = Parser::parseShip(gamer.placeShip());
				if (newShip.getWidth() != 1 || newShip.getLength() != 5 - count) {
					throw std::exception("incorrect ship format");
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

void Game::askShot(int turn)
{
	int correctShoot = 0;
	Gamer& gamer = (turn == 0 ? *gamer1.get() : *gamer2.get());
	std::vector<Shot>& shots = (turn == 0 ? shots1 : shots2);
	while (!correctShoot) {
		try {
			std::pair<int,int> cell = Parser::parseShot(gamer.shoot());
			correctShoot = 1;
			shots.push_back(handleCell(cell, turn));
		}
		catch (const std::exception & e) {
			std::cout << e.what() << std::endl;
		}
	}
}

Shot Game::handleCell(std::pair<int,int> cell, int turn)
{
	std::vector<Ship>& ships = (turn == 0 ? ships2 : ships1);
	for (auto& ship : ships) {
		for (int col = ship.getFirstSide().first; col <= ship.getSecondSide().first; col++) {
			for (int row = ship.getFirstSide().second; row <= ship.getSecondSide().second; row++) {
				if (cell == std::make_pair(col,row)) {
					ship.hit();
					return Shot(cell.first, cell.second, 1);
				}
			}
		}
	}
	return Shot(cell.first, cell.second, 0);
}

void Game::endRound()
{
	ships1.clear();
	ships2.clear();
	shots1.clear();
	shots2.clear();
}

int Game::checkWinner()
{
	int alive = 0;
	for (auto ship : ships1) {
		if (ship.getHP() != 0)alive = 1;
	}
	if (!alive)return 2;
	alive = 0;
	for (auto ship : ships2) {
		if (ship.getHP() != 0)alive = 1;
	}
	if (!alive)return 1;
	return 0;
}
