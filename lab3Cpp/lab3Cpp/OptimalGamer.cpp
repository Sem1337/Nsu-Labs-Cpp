#include "OptimalGamer.h"

OptimalGamer::OptimalGamer()
{
	reset();
}



OptimalGamer::~OptimalGamer()
{
}

std::string OptimalGamer::shoot()
{
	if (state == State::search) {
		std::pair<int, int> cell = Parser::parseShot(shotsOrder[currentShot]);
		while (shotsField[cell.second - 1][cell.first - 1] != '-') {
			cell = Parser::parseShot(shotsOrder[++currentShot]);
		}
		shotsField[cell.second - 1][cell.first - 1] = 'X';
		return shotsOrder[currentShot++];
	}
	else if (state == State::tryUpSide) {
		shotsField[foundUpSide - 1][foundLeftSide] = 'X';
		return std::string{ (char)(foundLeftSide + 'a') } + " " + std::to_string(foundUpSide);
	}
	else if (state == State::tryDownSide) {
		shotsField[foundDownSide + 1][foundLeftSide] = 'X';
		return std::string{ (char)(foundLeftSide + 'a') } + " " + std::to_string(foundDownSide + 2);
	}
	else if (state == State::tryLeftSide) {
		shotsField[foundUpSide][foundLeftSide - 1] = 'X';
		return std::string{ (char)(foundLeftSide - 1 + 'a') } + " " + std::to_string(foundUpSide + 1);
	}
	else if (state == State::tryRightSide) {
		shotsField[foundUpSide][foundRightSide + 1] = 'X';
		return std::string{ (char)(foundRightSide + 1 + 'a') } +" " + std::to_string(foundUpSide + 1);
	}
}



std::string OptimalGamer::placeShip()
{
	return shipsPlacement[currentShip++];
}

void OptimalGamer::setLastSuccessfulShot(Shot shot)
{
	lastShot = shot;
	if (lastShot.getType() == ShotStatus::Destroy) {
		updateFoundArea(shot.getPos());
		removeUselessShots();
		resetFoundArea();
		state = State::search;
	}
	else if (lastShot.getType() == ShotStatus::Hit) {
		updateFoundArea(shot.getPos());
		if (state == State::search) {
			nextState();
		}
		else if(!isValidState()){
			nextState();
		}
	}
	else if (lastShot.getType() == ShotStatus::Miss) {
		if (state != State::search) {
			nextState();
		}
	}
}

bool OptimalGamer::ready()
{
	return true;
}



void OptimalGamer::reset()
{
	shipsField.assign(10, std::vector<char>(10, '-'));
	shotsField.assign(10, std::vector<char>(10, '-'));
	shotsOrder.resize(100);
	shipsPlacement.clear();
	resetFoundArea();
	state = State::search;
	currentShot = 0;
	currentShip = 0;
	int shotsCounter = 0;
	int startRow = 4;
	for (char col = 'a'; col <= 'j'; col++) {
		for (int row = startRow; row <= 10; row += 4) {
			shotsOrder[shotsCounter++] = std::string{ col } +" " + std::to_string(row);
		}
		startRow--;
		if (startRow == 0)startRow = 4;
	}
	startRow = 2;
	for (char col = 'a'; col <= 'j'; col++) {
		for (int row = startRow; row <= 10; row += 4) {
			shotsOrder[shotsCounter++] = std::string{ col } +" " + std::to_string(row);
		}
		startRow--;
		if (startRow == 0)startRow = 4;
	}
	int staticStrategyShots = shotsCounter;
	startRow = 1;
	for (char col = 'a'; col <= 'j'; col++) {
		for (int row = startRow; row <= 10; row += 2) {
			shotsOrder[shotsCounter++] = std::string{ col } +" " + std::to_string(row);
		}
		startRow--;
		if (startRow == 0)startRow = 2;
	}
	std::random_shuffle(shotsOrder.begin() + staticStrategyShots, shotsOrder.end());

	makeOptimalShipsPlacement();

}





void OptimalGamer::makeOptimalShipsPlacement()
{
	placeVerticalShipOnShipsField('a', 1, 4);
	placeVerticalShipOnShipsField('c', 1, 3);
	placeVerticalShipOnShipsField('c', 5, 3);
	placeVerticalShipOnShipsField('a', 6, 2);
	placeVerticalShipOnShipsField('a', 9, 2);
	placeVerticalShipOnShipsField('c', 9, 2);
	for (int i = 0; i < 4; i++) {
		std::pair<char, int>availablePlace = findAvailablePlace();
		placeVerticalShipOnShipsField(availablePlace.first, availablePlace.second, 1);
	}
}


void OptimalGamer::placeVerticalShipOnShipsField(char col, int row, int size)
{

	for (int fieldRow = row - 1; fieldRow <= row - 1 + size - 1; fieldRow++) {   //  --XXXX--
		shipsField[fieldRow][col - 'a'] = 'X';
	}
	shipsPlacement.push_back(std::string{ col } +" " + std::to_string(row) + " " + col + " " + std::to_string(row + size - 1));
}

std::pair<char, int> OptimalGamer::findAvailablePlace()
{
	char col = 0;
	int row = 0;
	int correctPosition = 1;
	do {
		correctPosition = 1;
		col = 'a' + rand() % 10;
		row = 1 + rand() % 10;

		for (int fieldCol = col - 'a' - 1; fieldCol <= col - 'a' + 1; fieldCol++) {   //  --XXXX--
			if (fieldCol < 0 || fieldCol >= 10)continue;
			for (int fieldRow = row - 2; fieldRow <= row; fieldRow++) {
				if (fieldRow < 0 || fieldRow >= 10)continue;
				if (shipsField[fieldRow][fieldCol] != '-') {
					correctPosition = 0;
					break;
				}
			}
			if (!correctPosition)break;
		}

	} while (!correctPosition);

	return { col,row };
}

void OptimalGamer::updateFoundArea(std::pair<int, int>pos)
{
	int col = pos.first;
	int row = pos.second;
	foundLeftSide = min(foundLeftSide, col - 1);
	foundRightSide = max(foundRightSide, col - 1);
	foundDownSide = max(foundDownSide, row - 1);
	foundUpSide = min(foundUpSide, row - 1);
}

void OptimalGamer::removeUselessShots()
{
	for (int col = foundLeftSide - 1; col <= foundRightSide + 1; col++) {
		if (col < 0 || col >= 10)continue;
		for (int row = foundUpSide - 1; row <= foundDownSide + 1; row++) {
			if (row < 0 || row >= 10)continue;
			shotsField[row][col] = 'X';
		}
	}
}

void OptimalGamer::nextState()
{
	if (state == State::search) {
		state = State::tryUpSide;
	}
	else if (state == State::tryUpSide) {
		state = State::tryDownSide;
	}
	else if (state == State::tryDownSide) {
		state = State::tryLeftSide;
	}
	else if (state == State::tryLeftSide) {
		state = State::tryRightSide;
	}
	else {
		state = State::search;
	}

	if (!isValidState()) {
		nextState();
	}
}

void OptimalGamer::resetFoundArea()
{
	foundDownSide = -1;
	foundUpSide = 15;
	foundLeftSide = 15;
	foundRightSide = -1;
}

bool OptimalGamer::isValidState()
{
	if (state == State::tryUpSide) {
		if (foundUpSide - 1 < 0 || shotsField[foundUpSide - 1][foundLeftSide] != '-') {
			return false;
		}
	}
	else if (state == State::tryDownSide) {
		if (foundDownSide + 1 >= 10 || shotsField[foundDownSide + 1][foundLeftSide] != '-') {
			return false;
		}
	}
	else if (state == State::tryLeftSide) {
		if (foundLeftSide - 1 < 0 || shotsField[foundDownSide][foundLeftSide - 1] != '-') {
			return false;
		}
	}
	else if (state == State::tryRightSide) {
		if (foundRightSide + 1 >= 10 || shotsField[foundDownSide][foundRightSide + 1] != '-') {
			return false;
		}
	}
	return true;
}
