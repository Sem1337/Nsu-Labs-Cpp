#include "ConsoleGamer.h"

ConsoleGamer::ConsoleGamer()
{
}

ConsoleGamer::~ConsoleGamer()
{
}

std::string ConsoleGamer::shoot()
{
	std::string cell;
	std::getline(std::cin, cell);
	return cell;
}

std::string ConsoleGamer::placeShip()
{
	std::string ship;
	std::getline(std::cin, ship);
	return ship;
}

void ConsoleGamer::setLastSuccessfulShot(Shot shot)
{
	return;
}

bool ConsoleGamer::ready()
{
	std::cout << "ready to next round? (y/n)\n";
	std::string c;
	std::getline(std::cin, c);
	return c == "y";
}

void ConsoleGamer::reset()
{
}
