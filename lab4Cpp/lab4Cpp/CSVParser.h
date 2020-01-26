#pragma once
#include <tuple>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ParsingException.h"
template<typename Head, typename... Tail>
std::tuple<Tail...> tuple_tail(std::tuple<Head, Tail...> const& t) {
	return std::apply([](Head head, auto... tail) { return std::make_tuple(tail...); }, t);
}

template<typename Ch, typename Tr, typename Type>
auto& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Type> const& t) {
	os << std::get<0>(t);
	return os;
}

template<typename Ch, typename Tr, typename... Args>
auto& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) {
	os << std::get<0>(t) << " ";
	os << tuple_tail(t);
	return os;
}

template<size_t N, typename... Args>
typename std::enable_if<N==0>::type
fillTuple(std::vector<std::string> const& tokens, std::tuple<Args...>& t) {
	std::stringstream ss(tokens[N]);
	ss >> std::get<N>(t);
}

template<size_t N,typename... Args>
typename std::enable_if<N!=0>::type
fillTuple(std::vector<std::string> const& tokens, std::tuple<Args...>& t) {
	std::stringstream ss(tokens[N]);
	ss >> std::get<N>(t);
	if (!ss) {
		throw ParsingException(N + 1);
	}
	fillTuple<N - 1>(tokens, t);
}

template<class... Args >
class CSVParser {
public:
	CSVParser(std::ifstream& in, int skippedLines, char columnSeparator = ';', char rowSeparator = '\n') : in(in), columnSeparator(columnSeparator), rowSeparator(rowSeparator), firstLineIdx(skippedLines) {
		for (firstLineIdx = 0; firstLineIdx < skippedLines && !(this->in.eof()); firstLineIdx++) {
			std::string line;
			std::getline(this->in, line, rowSeparator);
		}
		startPosition = in.tellg();
	}

	class Iterator;

	Iterator begin() {
		in.seekg(startPosition, std::ios_base::beg);
		return Iterator(in, firstLineIdx, columnSeparator, rowSeparator);
	}

	Iterator end() {
		return Iterator(in, -1, columnSeparator, rowSeparator);
	}

	class Iterator {
	public:
		Iterator(std::ifstream& in, int skippedLines, char columnSeparator = ';', char rowSeparator = '\n') : in(in), columnSeparator(columnSeparator), rowSeparator(rowSeparator) {
			lineIdx = skippedLines;
			if (!in.eof() && lineIdx!=-1) {
				readLine();
			}
		}

		std::tuple<Args...>& operator* () {
			if (lineIdx == -1) {
				throw std::exception("dereference out of range");
			}
			return args;
		}

		Iterator& operator++() {
			if (in.eof()) {
				lineIdx = -1;
				return *this;
			}
			readLine();
			return *this;
		}

		bool operator==(Iterator const& it) {
			return (this->lineIdx == it.lineIdx);
		}
		bool operator!=(Iterator const& it) {
			return !(*this == it);
		}

	private:
		void readLine() {
			std::string line;
			std::getline(in, line, rowSeparator);
			if (line == "") {
				lineIdx = -1;
				return;
			}
			try {
				tokenize(line);
				lineIdx++;
			}
			catch (ParsingException const& e) {
				std::cout << e.message() << std::endl;
				lineIdx = -1;
			}
		}

		void tokenize(std::string& line) {
			std::vector<std::string> tokens(std::tuple_size<std::tuple<Args...>>::value);
			std::stringstream ss(line);
			for (int column = 0; column < std::tuple_size<std::tuple<Args...>>::value; column++) {
				std::getline(ss, tokens[column], columnSeparator);
			}
			try {
				fillTuple<std::tuple_size<std::tuple<Args...>>::value - 1>(tokens, args);
			}
			catch (ParsingException const& e) {
				throw ParsingException(e.getCol(), lineIdx);
			}
		}

		char columnSeparator;
		char rowSeparator;
		int lineIdx;
		std::ifstream &in;
		std::tuple<Args...> args;
	};

private:
	std::streamoff startPosition;
	int firstLineIdx;
	char columnSeparator;
	char rowSeparator;
	std::ifstream& in;
};