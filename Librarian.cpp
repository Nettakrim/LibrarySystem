#include "Librarian.h"

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

void Librarian::openUI()
{
	std::cout << "librarian!!!";
}
