#include <iostream>
#include <string>
#include <vector>
#include "ConsoleView.h"
#include "optionparser.h"
#include "Game.h"

struct Arg : public option::Arg
{
	static void printError(const char* msg1, const option::Option& opt, const char* msg2)
	{
		fprintf(stderr, "ERROR: %s", msg1);
		fwrite(opt.name, opt.namelen, 1, stderr);
		fprintf(stderr, "%s", msg2);
	}

	static option::ArgStatus GamerType(const option::Option& option, bool msg)
	{
		char* endptr = 0;
		int num = 0;
		if (option.arg !=0) {
			num = strtol(option.arg, &endptr, 10);
		};
		if (endptr != option.arg && *endptr == 0 && num >= 1 && num <= 3)
			return option::ARG_OK;
		if (msg) printError("Option '", option, "' incorrect argument argument\n");
		return option::ARG_ILLEGAL;
	}

	static option::ArgStatus RoundsCount(const option::Option& option, bool msg)
	{
		char* endptr = 0;
		int num = 0;
		if (option.arg != 0) {
			num = strtol(option.arg, &endptr, 10);
		};
		if (endptr != option.arg && *endptr == 0)
			return option::ARG_OK;
		if (msg) printError("Option '", option, "' incorrect argument argument\n");
		return option::ARG_ILLEGAL;
	}

};

enum  optionIndex { UNKNOWN, HELP, COUNT, FIRST, SECOND };
const option::Descriptor usage[] =
{
 {UNKNOWN, 0, "", "",option::Arg::None, "USAGE: example [options]\n\n"
										"Options:" },
 {HELP, 0,"h", "help",option::Arg::None, "--help, -h  \tPrint usage and exit." },
 {COUNT, 0,"c","count",Arg::RoundsCount, "--count, -c  \tSet count of rounds." },
 {FIRST, 0, "f", "first",Arg::GamerType, "--first, -f \tSet first player type.\n(1 - console gamer, 2 - random gamer, 3 - optimal gamer) default = 2\n"},
 {SECOND, 0, "s", "second",Arg::GamerType, "--second, -s \tSet second player type.\n(1 - console gamer, 2 - random gamer, 3 - optimal gamer) default = 2\n"},
};

int main(int argc, char* argv[])
{
	argc -= (argc > 0); argv += (argc > 0);
	option::Stats  stats(usage, argc, argv);
	std::vector<option::Option> options(stats.options_max);
	std::vector<option::Option> buffer(stats.buffer_max);
	option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

	if (parse.error())
		return 1;

	if (options[HELP]) {
		option::printUsage(std::cout, usage);
		return 0;
	}

	int roundCount = options[COUNT].arg == 0 ? 2 : atoi(options[COUNT].arg);
	int gamerType1 = options[FIRST].arg == 0 ? 2 : atoi(options[FIRST].arg);
	int gamerType2 = options[SECOND].arg == 0 ? 3 : atoi(options[SECOND].arg);
	
	Game game(roundCount, gamerType1, gamerType2, PresenterType::ConsolePresent);
	game.run();

}
