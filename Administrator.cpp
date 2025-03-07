#include "Administrator.h"
#include "Util.h"

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

bool Administrator::loopUI()
{
	std::cout << "admin!!!\n";
	
	int option = Util::getOption({ "???" }, "Log Out");

	return option != 0;
}
