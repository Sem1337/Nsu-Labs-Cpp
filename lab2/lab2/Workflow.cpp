#include "Workflow.h"

Workflow::Workflow(std::string fileName, std::string in, std::string out)
{
	ReadFile *reader = new ReadFile(fileName, data);
	reader->execute();
	if (!in.empty()) {
		this->in.open(in);
	}
	if (!out.empty()) {
		this->out.open(out);
	}
	SchemeValidator* schemeValidator = new SchemeValidator(data);
	if (!schemeValidator->isValid()) {
	
	}
	else {
		SchemeParser *schemeParser = new SchemeParser(data);
		schemeParser->parse();
	}
}

Workflow::~Workflow()
{
}
