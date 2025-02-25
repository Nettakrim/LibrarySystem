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
