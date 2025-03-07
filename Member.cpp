#include "Member.h"

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

void Member::openUI()
{
	std::cout << "member!!!";
}
