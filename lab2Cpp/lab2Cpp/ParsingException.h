#pragma once
#include <exception>
class ParsingException :
	public std::exception
{
public:
	ParsingException();
	ParsingException(const char*);
	virtual const char* what() const noexcept override;
private:
	const char* message;
};

