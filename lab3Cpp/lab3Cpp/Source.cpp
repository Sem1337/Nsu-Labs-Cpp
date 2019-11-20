#include <iostream>
#include <string>
#include <vector>
#include "optionparser.h"

enum  optionIndex { UNKNOWN, HELP, COUNT, FIRST, SECOND };
const option::Descriptor usage[] =
{
 {UNKNOWN, 0, "", "",option::Arg::None, "USAGE: example [options]\n\n"
										"Options:" },
 {HELP, 0,"h", "help",option::Arg::None, "--help, -h  \tPrint usage and exit." },
 {COUNT, 0,"c","count",option::Arg::Optional, "--count, -c  \tSet count of rounds." },
 {FIRST, 0, "f", "first",option::Arg::Optional, "--first, -f \tSet first player type."},
 {SECOND, 0, "s", "second",option::Arg::Optional, "--second, -s \tSet second player type."},
};

int main(int argc, char* argv[])
{
	argc -= (argc > 0); argv += (argc > 0); // skip program name argv[0] if present
	option::Stats  stats(usage, argc, argv);
	std::vector<option::Option> options(stats.options_max);
	std::vector<option::Option> buffer(stats.buffer_max);
	option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

	if (parse.error())
		return 1;

	if (options[HELP] || argc == 0) {
		option::printUsage(std::cout, usage);
		return 0;
	}

	std::cout << "--plus count: " <<
		options[COUNT].count() << "\n";

	for (option::Option* opt = options[UNKNOWN]; opt; opt = opt->next())
		std::cout << "Unknown option: " << std::string(opt->name, opt->namelen) << "\n";

	for (int i = 0; i < parse.nonOptionsCount(); ++i)
		std::cout << "Non-option #" << i << ": " << parse.nonOption(i) << "\n";
}
