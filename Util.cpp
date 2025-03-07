#include "Util.h"

#include <iostream>

std::string lineClear;

void Util::awaitEnter()
{
	std::getline(std::cin, lineClear);
}

int Util::getOption(std::vector<std::string> options, std::string backMessage)
{
	size_t count = options.size();
	std::string s;
	int o;

	for (int i = 0; i < count; i++) {
		std::cout << i + 1 << ". " << options[i] << "\n";
	}
	std::cout << "0. " << backMessage << "\n" << optionPrompt;

	while (true) {
		std::getline(std::cin, s);
		o = std::atoi(s.c_str());

		if ((o > 0 && o <= count) || s == "0") {
			std::cout << CLEAR_AFTER;
			return o;
		}

		std::cout << "Invalid Input (0-" << count << ")" << MOVE_TO_LINE_START << CLEAR_AFTER << optionPrompt;
	}
}

int Util::getOption(std::vector<std::string> options)
{
	return getOption(options, "Back");
}
