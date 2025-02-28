#include "Book.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

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

	while (std::getline(file, line)) {
		std::cout << line;
	}
}

void Book::saveData(std::ofstream& file)
{
	file << "book\n";
	file << "hello!";
}
