#include "Book.h"

Book::Book(std::string filename) : Item(filename)
{

}

int Book::getType() const
{
	return 0;
}

Book::~Book()
{

}

Book::Book(std::string filename, std::ifstream& file) : Item(filename)
{
	std::getline(file, title);
	std::getline(file, author);
}

void Book::saveData(std::ofstream& file)
{
	file << "book\n";
	file << title << "\n";
	file << author << "\n";
}

std::string Book::getListDisplay() const
{
	std::string display = title;

	while (display.size() < 30) {
		display.push_back(' ');
	}

	display += " - " + author;

	while (display.size() < 55) {
		display.push_back(' ');
	}

	display += " - " + Item::getStateName(getState());

	return display;
}

std::string Book::getDescription() const
{
	return "hi!";
}

std::vector<std::string> Book::getInfoFields() const
{
	return { "Title", "Author" };
}

std::string Book::getInfoValue(int field) const
{
	switch (field) {
	case 0:
		return title;
	case 1:
		return author;
	default:
		return "";
	};
}