#pragma once
#include <exception>
class ValidationException :
	public std::exception
{
public:
	ValidationException();
	ValidationException(const char*);
	virtual const char* what() const noexcept override;
private:
	const char* message;
};

