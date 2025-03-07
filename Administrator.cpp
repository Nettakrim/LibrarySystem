#include "Administrator.h"

Administrator::Administrator(std::string filename, std::ifstream& file) : User(filename)
{
	std::getline(file, username);
	std::getline(file, password);
}

void Administrator::saveData(std::ofstream& file)
{
	file << "administrator\n";
	file << username << "\n";
	file << password << "\n";
}

void Administrator::openUI()
{
	std::cout << "admin!!!";
}
