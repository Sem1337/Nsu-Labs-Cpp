#include "Sort.h"

Sort::Sort(std::vector<std::string>& data) : data(data)
{
}

Sort::~Sort()
{
}

void Sort::execute()
{
	sort(data.begin(), data.end());
}

DataType Sort::input() const
{
	return DataType::Text;
}

DataType Sort::output() const
{
	return DataType::Text;
}

