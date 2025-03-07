#include "Book.h"

Book::Book(std::string filename) : Item(filename)
{

}

Book::~Book()
{

}

std::string Book::getDescription()
{
	return "hi!";
}

Book::Book(std::string filename, std::ifstream& file) : Item(filename)
{
	std::string line;
}

void Book::saveData(std::ofstream& file)
{
	file << "book\n";
}
