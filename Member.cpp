#include "Member.h"
#include "Util.h"

Member::Member(std::string filename, std::ifstream& file) : User(filename)
{
	std::getline(file, username);
	std::getline(file, password);
}

void Member::saveData(std::ofstream& file)
{
	file << "member\n";
	file << username << "\n";
	file << password << "\n";
}

bool Member::loopUI()
{
	std::cout << "member!!!\n";

	int option = Util::getOption({ "???" }, "Log Out");

	return option != 0;
}
