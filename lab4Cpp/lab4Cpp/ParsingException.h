#pragma once
#include <exception>
#include <string>
class ParsingException : std::exception
{
public:
	ParsingException(int col, int row = -1): col(col), row(row) {
		
	}

	std::string message() const {
		return "wrong format at line " + std::to_string(row+1) + " column " + std::to_string(col);
	}

	int getCol() const {
		return col;
	}

	int getRow() const {
		return row;
	}

private:
	int col;
	int row;

};

