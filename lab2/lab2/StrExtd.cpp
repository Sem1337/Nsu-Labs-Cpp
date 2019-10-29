#include "StrExtd.h"
namespace StrExtd {
	std::vector<std::string> tokenize(const std::string& input, char separator)
	{
		std::vector<std::string> tokenizedString;
		std::string token;
		std::stringstream stream(input);
		while (std::getline(stream, token, separator)) {
			tokenizedString.push_back(token);
		}
		return tokenizedString;
	}
}