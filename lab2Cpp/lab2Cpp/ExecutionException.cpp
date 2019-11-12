#include "ExecutionException.h"

ExecutionException::ExecutionException() : message("Execution exception")
{
}

ExecutionException::ExecutionException(const char* message) : message(message)
{
}


const char* ExecutionException::what() const noexcept
{
	return message;
}
