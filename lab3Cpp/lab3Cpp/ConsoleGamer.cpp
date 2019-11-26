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
	std::string cell;
	std::getline(std::cin, cell);
	return cell;
}
