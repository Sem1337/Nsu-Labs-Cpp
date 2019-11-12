#include "ValidationException.h"

ValidationException::ValidationException() : message("Validation exception")
{
}

ValidationException::ValidationException(const char* message) : message(message)
{
}

const char* ValidationException::what() const noexcept
{
	return message;
}
