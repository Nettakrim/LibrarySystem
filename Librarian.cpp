#include "Librarian.h"
#include "Util.h"

Librarian::Librarian(std::string filename) : User(filename)
{
}

Librarian::Librarian(std::string filename, std::ifstream& file) : User(filename)
{
	std::getline(file, username);
	std::getline(file, password);
}

void Librarian::saveData(std::ofstream& file)
{
	file << "librarian\n";
	file << username << "\n";
	file << password << "\n";
}

bool Librarian::loopUI()
{
	std::cout << "librarian!!!\n";

	int option = Util::getOption({ "???" }, "Log Out");

	return option != 0;
}
