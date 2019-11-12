#include "Workflow.h"

Workflow::Workflow(const std::string& fileName,const std::string& in,const std::string& out)
{

	std::unique_ptr<ReadFile>reader(new ReadFile(data, std::vector<std::string>() = { "readfile", fileName }));
	reader->execute();

	try {
		std::unique_ptr<SchemeValidator>schemeValidator(new SchemeValidator(data));
		schemeValidator->validation();
		std::unique_ptr<SchemeParser> schemeParser(new SchemeParser(data));

		try {
			schemeParser->parse();
		}
		catch (...) {
			throw ParsingException();
		}
		std::unique_ptr<Scheme> scheme(new Scheme(schemeParser->getBlocksDescription(), schemeParser->getParsedSequence(), in, out));

		scheme->execute();

	}
	catch (const ParsingException & e) {
		std::cerr << e.what();
	}
	catch (const ExecutionException & e) {
		std::cerr << e.what();
	}
	catch (const ValidationException & e) {
		std::cerr << e.what();
	}

}

Workflow::~Workflow()
{
}
