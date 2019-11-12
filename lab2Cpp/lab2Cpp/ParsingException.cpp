#include "ParsingException.h"

ParsingException::ParsingException() : message("Parsing exception")
{
}

ParsingException::ParsingException(const char* message) : message(message)
{
}

const char* ParsingException::what() const noexcept
{
	return message;
}
