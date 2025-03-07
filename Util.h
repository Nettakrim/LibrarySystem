#pragma once

#include <string>
#include <vector>

namespace Util {
	const inline char* CLEAR_ALL = "\33[2J\33[1;1H";
	const inline char* CLEAR_AFTER = "\33[2K";
	const inline char* MOVE_TO_LINE_START = "\33[0F";

	const inline char* optionPrompt = ": ";

	void awaitEnter();

	int getOption(std::vector<std::string> options, std::string backMessage);

	int getOption(std::vector<std::string> options);
}
