#include "WriteFile.h"

WriteFile::WriteFile(const std::vector<std::string>& data, const std::vector<std::string>& arguments) : fileName(arguments[1]), data(data)
{
}

WriteFile::~WriteFile()
{
}

void WriteFile::execute()
{
	std::ofstream out(fileName);
	int linesCount = data.size();
	for (int i = 0; i < linesCount; i++) {
		out << data[i] << std::endl;
	}
	out.close();
}

DataType WriteFile::input() const
{
	return DataType::Text;
}

DataType WriteFile::output() const
{
	return DataType::Void;
}

