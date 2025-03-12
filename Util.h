#pragma once

#include <string>
#include <vector>

namespace Util {
	const inline char* ESC = "\33[";

	const inline char* CLEAR_ALL = "\33[2J\33[1;1H";
	const inline char* CLEAR_LINE_AFTER = "\33[0K";
	const inline char* CLEAR_ALL_AFTER = "\33[0J";

	const inline char* MOVE_TO_LINE_START = "\33[0F";
	const inline char* SAVE_CURSOR_POS = "\033[s";
	const inline char* LOAD_CURSOR_POS = "\033[u";

	const inline char* optionPrompt = ": ";

	void awaitEnter();

	int getOption(std::vector<std::string> options, std::string backMessage);

	int getOption(std::vector<std::string> options);

	void moveBackAndClear(int lines);

	std::string toLower(std::string s);

	std::string makeFileSafe(std::string filename);

	time_t getUnixTime();
}
