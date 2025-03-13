#include "Util.h"

#include <iostream>
#include <ctime>

void Util::awaitEnter()
{
	std::string lineClear;
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
			std::cout << CLEAR_LINE_AFTER;
			return o;
		}

		std::cout << "Invalid Input (0-" << count << ")" << MOVE_TO_LINE_START << CLEAR_LINE_AFTER << optionPrompt;
	}
}

int Util::getOption(std::vector<std::string> options)
{
	return getOption(options, "Back");
}

std::string Util::getStringInput(std::string message, bool allowEmpty)
{
	std::string input;
	while (true) {
		std::cout << message << ": ";
		std::getline(std::cin, input);
		if (allowEmpty || input != "") {
			return input;
		}

		std::cout << MOVE_TO_LINE_START << CLEAR_LINE_AFTER;
	}
}

void Util::moveBackAndClear(int lines)
{
	std::cout << ESC << lines << "A" << MOVE_TO_LINE_START << CLEAR_ALL_AFTER;
}

std::string Util::toLower(std::string s)
{
	for (int i = 0; i < s.size(); i++) {
		s[i] = tolower(s[i]);
	}
	return s;
}

std::string Util::makeFileSafe(std::string filename) {
	if (filename.size() > 32) {
		filename = filename.substr(0, 32);
	}

	std::string dissalowed = "\\/:*?\"<>|";
	for (int i = 0; i < filename.size(); i++) {
		if (dissalowed.find(filename[i]) != std::string::npos) {
			filename[i] = '_';
		}
	}

	filename = toLower(filename);

	return filename;
}

time_t Util::getUnixTime()
{
	time_t t;
	time(&t);
	return t;
}
