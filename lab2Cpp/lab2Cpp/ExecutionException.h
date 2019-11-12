#pragma once
#include <exception>
#include <string>
class ExecutionException :
	public std::exception
{
public:
	ExecutionException();
	ExecutionException(const char*);

	virtual const char* what() const noexcept override;
private:
	const char* message;
};

