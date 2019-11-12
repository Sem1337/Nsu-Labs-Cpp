#include "Dump.h"

Dump::Dump(const std::vector<std::string>& data,const std::vector<std::string>& arguments) : fileName(arguments[1]) , data(data)
{
}

Dump::~Dump()
{
}

void Dump::execute()
{
	WriteFile(data, std::vector<std::string>() = {"writefile", fileName }).execute();
}

enum DataType Dump::input() const
{
	return DataType::Text;
}

enum DataType Dump::output() const
{
	return DataType::Text;
}
