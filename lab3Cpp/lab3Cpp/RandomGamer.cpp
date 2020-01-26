#include "RandomGamer.h"

RandomGamer::RandomGamer()
{
	reset();
}

RandomGamer::~RandomGamer()
{
}

void RandomGamer::makeShipsPlacement()
{
	for (int shipSize = 4; shipSize >= 1; shipSize--) {
		int shipsCount = 5 - shipSize;
		for (int ship = shipsCount; ship > 0; ship--) {
			if (rand() % 2) {
				putHorizontally(shipSize);
			}
			else {
				putVertically(shipSize);
			}
		}
	}
}

void RandomGamer::putHorizontally(int size)
{
	char col = 0;
	int row = 0;
	int correctPosition = 1;
	do{
		correctPosition = 1;
		col = 'a' + rand() % (11 - size);
		row = 1 + rand() % 10;													 //  --------
		for (int fieldCol = col - 'a' - 1; fieldCol <= col - 'a' + size; fieldCol++) {   //  --XXXX--
			if (fieldCol < 0 || fieldCol >= 10)continue;
			for (int fieldRow = row - 2; fieldRow <= row; fieldRow++) {
				if (fieldRow < 0 || fieldRow >= 10)continue;
				if (field[fieldRow][fieldCol] != '-') {
					correctPosition = 0;
					break;
				}
			}
			if (!correctPosition)break;
		}
	} while (!correctPosition);

	for (int fieldCol = col - 'a'; fieldCol <= col - 'a' + size - 1; fieldCol++) {   //  --XXXX--
		field[row - 1][fieldCol] = 'X';
	}
	shipsPlacement.push_back(std::string{ col } +" " + std::to_string(row) + " " + (char)(col + size - 1) + " " + std::to_string(row));
}

void RandomGamer::putVertically(int size)
{
	char col = 0;
	int row = 0;
	int correctPosition = 1;
	do {
		correctPosition = 1;
		col = 'a' + rand() % 10;
		row = 1 + rand() % (11 - size);

		for (int fieldCol = col - 'a' - 1; fieldCol <= col - 'a' + 1; fieldCol++) {   //  --XXXX--
			if (fieldCol < 0 || fieldCol >= 10)continue;
			for (int fieldRow = row - 2; fieldRow <= row + size - 1; fieldRow++) {
				if (fieldRow < 0 || fieldRow >= 10)continue;
				if (field[fieldRow][fieldCol] != '-') {
					correctPosition = 0;
					break;
				}
			}
			if (!correctPosition)break;
		}

	} while (!correctPosition);

	for (int fieldRow = row - 1; fieldRow <= row - 1 + size - 1; fieldRow++) {   //  --XXXX--
		field[fieldRow][col - 'a'] = 'X';
	}

	shipsPlacement.push_back(std::string{ col } +" " + std::to_string(row) + " " + col + " " + std::to_string(row + size - 1));
}

std::string RandomGamer::shoot()
{
	return shotsOrder[currentShot++];
}

std::string RandomGamer::placeShip()
{
	return shipsPlacement[currentShip++];
}

void RandomGamer::setLastSuccessfulShot(Shot shot)
{
	return;
}

bool RandomGamer::ready()
{
	return true;
}

void RandomGamer::reset()
{
	currentShip = 0;
	currentShot = 0;
	shotsOrder.resize(100);
	shipsPlacement.clear();
	for (char col = 'a'; col <= 'j'; col++) {
		for (int row = 1; row <= 10; row++) {
			shotsOrder[(col - 'a') * 10 + row - 1] = std::string{ col } +" " + std::to_string(row);
		}
	}
	std::random_shuffle(shotsOrder.begin(), shotsOrder.end());
	field.assign(10, std::vector<char>(10, '-'));
	makeShipsPlacement();
}




