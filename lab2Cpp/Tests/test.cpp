#include "pch.h"
#include "Workflow.cpp"
#include "Dump.cpp"
#include "DumpParser.cpp"
#include "DumpValidator.cpp"
#include "Grep.cpp"
#include "GrepParser.cpp"
#include "GrepValidator.cpp"
#include "Replace.cpp"
#include "ReplaceParser.cpp"
#include "ReplaceValidator.cpp"
#include "ReadFile.cpp"
#include "ReadFileParser.cpp"
#include "ReadFileValidator.cpp"
#include "WriteFile.cpp"
#include "WriteFileParser.cpp"
#include "WriteFileValidator.cpp"
#include "Sort.cpp"
#include "SortParser.cpp"
#include "SortValidator.cpp"
#include "Scheme.cpp"
#include "SchemeParser.cpp"
#include "SchemeValidator.cpp"
#include "ExecutionException.cpp"
#include "ParsingException.cpp"
#include "ValidationException.cpp"
#include "StrExtd.cpp"

std::vector<std::string>readfile(const std::string name) {
	std::vector<std::string>text;
	std::ifstream in(name);
	std::string nextLine;
	while (std::getline(in, nextLine)) {
		text.push_back(nextLine);
	}
	in.close();
	return text;
}

TEST(TestFirstScheme, FirstCorrectScheme) {
	
	std::vector<std::string>correctFirstOut = readfile("../lab2Cpp/work/correctFirstOut.txt");
	std::vector<std::string>correctFirstDump = readfile("../lab2Cpp/work/correctFirstDump.txt");

	EXPECT_NO_THROW(Workflow workflow("../lab2Cpp/work/firstWorkflow.txt"));

	std::vector<std::string>firstOut = readfile("../lab2Cpp/work/firstOutput.txt");
	std::vector<std::string>firstDump = readfile("../lab2Cpp/work/firstDump.txt");

	EXPECT_EQ(correctFirstDump.size(), firstDump.size());

	for (size_t line = 0; line < correctFirstDump.size(); line++) {
		EXPECT_STREQ(correctFirstDump[line].c_str(), firstDump[line].c_str());
	}

	EXPECT_EQ(correctFirstOut.size(), firstOut.size());
	for (size_t line = 0; line < correctFirstOut.size(); line++) {
		EXPECT_STREQ(correctFirstOut[line].c_str(), firstOut[line].c_str());
	}
	
}


TEST(TestSecondScheme, MoreThanOneDefinitions) {

	std::vector<std::string>secondWorkflow = readfile("../lab2Cpp/work/secondWorkflow.txt");
	std::unique_ptr<SchemeValidator> schemeValidator = std::make_unique<SchemeValidator>(secondWorkflow);
	EXPECT_THROW(schemeValidator->validation(), ValidationException);

}


TEST(TestThirdScheme, IncorrectIdInSequence) {

	std::vector<std::string>thirdWorkflow = readfile("../lab2Cpp/work/thirdWorkflow.txt");
	std::unique_ptr<SchemeValidator> schemeValidator = std::make_unique<SchemeValidator>(thirdWorkflow);
	EXPECT_THROW(schemeValidator->validation(), ValidationException);

}

TEST(TestFourthScheme, IncorrectOrder) {

	std::vector<std::string>fourthWorkflow = readfile("../lab2Cpp/work/fourthWorkflow.txt");
	std::unique_ptr<SchemeValidator> schemeValidator = std::make_unique<SchemeValidator>(fourthWorkflow);
	schemeValidator->validation();
	std::unique_ptr<SchemeParser> schemeParser = std::make_unique<SchemeParser>(fourthWorkflow);
	schemeParser->parse();
	std::unique_ptr<Scheme> scheme = std::make_unique<Scheme>(schemeParser->getBlocksDescription(), schemeParser->getParsedSequence());
	EXPECT_THROW(scheme->execute(), ExecutionException);

}

TEST(TestFifthScheme, ExcessArgument) {

	std::vector<std::string>fifthWorkflow = readfile("../lab2Cpp/work/fifthWorkflow.txt");
	std::unique_ptr<SchemeValidator> schemeValidator = std::make_unique<SchemeValidator>(fifthWorkflow);
	EXPECT_THROW(schemeValidator->validation(), ValidationException);

}

TEST(TestSixthScheme, WrongFileName) {

	std::vector<std::string>sixthWorkflow = readfile("../lab2Cpp/work/sixthWorkflow.txt");
	std::unique_ptr<SchemeValidator> schemeValidator = std::make_unique<SchemeValidator>(sixthWorkflow);
	schemeValidator->validation();
	std::unique_ptr<SchemeParser> schemeParser = std::make_unique<SchemeParser>(sixthWorkflow);
	schemeParser->parse();
	std::unique_ptr<Scheme> scheme = std::make_unique<Scheme>(schemeParser->getBlocksDescription(), schemeParser->getParsedSequence());
	EXPECT_THROW(scheme->execute(), ExecutionException);

}

TEST(TestSeventhScheme, SecondCorrectScheme) {

	EXPECT_NO_THROW(Workflow workflow("../lab2Cpp/work/seventhWorkflow.txt"));

	std::vector<std::string>out = readfile("../lab2Cpp/work/seventhOutput.txt");
	EXPECT_TRUE(out.empty());
}



TEST(TestEighthScheme, ThirdCorrectScheme) {

	std::vector<std::string>correctFirstOut = readfile("../lab2Cpp/work/correctFirstOut2.txt");
	std::vector<std::string>correctSecondOut = readfile("../lab2Cpp/work/correctSecondOut2.txt");

	EXPECT_NO_THROW(Workflow workflow("../lab2Cpp/work/eighthWorkflow.txt"));

	std::vector<std::string>firstOut = readfile("../lab2Cpp/work/firstOutput.txt");
	std::vector<std::string>secondOut = readfile("../lab2Cpp/work/secondOutput.txt");

	EXPECT_EQ(correctFirstOut.size(), firstOut.size());

	for (size_t line = 0; line < correctFirstOut.size(); line++) {
		EXPECT_STREQ(correctFirstOut[line].c_str(), firstOut[line].c_str());
	}

	EXPECT_EQ(correctSecondOut.size(), secondOut.size());

	for (size_t line = 0; line < correctSecondOut.size(); line++) {
		EXPECT_STREQ(correctSecondOut[line].c_str(), secondOut[line].c_str());
	}

}

