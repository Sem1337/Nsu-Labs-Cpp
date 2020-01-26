#include "Parser.h"

std::pair<int,int> Parser::parseShot(std::string shoot)
{
	int row, col;
	std::vector<std::string>tokenized = tokenize(shoot);
	if (tokenized.size() != 2 || tokenized[0].size()!=1)throw std::exception("incorrect move");
	col = tokenized[0][0] - 'a' + 1;
	row = atoi(tokenized[1].c_str());
	if (col < 1 || col > 10 || row < 1 || row > 10)throw std::exception("incorrect move");
	return { col, row };
}

Ship Parser::parseShip(std::string ship)
{
	std::pair<int, int>firstSide;
	std::pair<int, int>secondSide;
	std::vector<std::string>tokenized = tokenize(ship);
	if (tokenized.size() == 2) {
		tokenized.push_back(tokenized[0]);
		tokenized.push_back(tokenized[1]);
	}
	if (tokenized.size() != 4 || tokenized[0].size() != 1 || tokenized[2].size() != 1)throw std::exception("incorrect ship format");
	firstSide = { tokenized[0][0] - 'a' + 1,atoi(tokenized[1].c_str()) };
	secondSide = { tokenized[2][0] - 'a' + 1, atoi(tokenized[3].c_str()) };
	if (firstSide.first < 1 || firstSide.first > 10
		|| firstSide.second < 1 || firstSide.second > 10
		|| secondSide.first < 1 || secondSide.first > 10
		|| secondSide.second < 1 || secondSide.second > 10)throw std::exception("incorrect ship position");
	return Ship(firstSide, secondSide);
}

std::vector<std::string> Parser::tokenize(const std::string& input, char separator)
{
	std::vector<std::string> tokenizedString;
	std::string token;
	std::stringstream stream(input);
	while (std::getline(stream, token, separator)) {
		tokenizedString.push_back(token);
	}
	return tokenizedString;
}
