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
	std::getline(file, description);
}

void Book::saveData(std::ofstream& file)
{
	file << "book\n";
	file << title << "\n";
	file << author << "\n";
	file << description << "\n";
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
	return description;
}

std::vector<std::string> Book::getInfoFields() const
{
	return { "Title", "Author", "Description" };
}

std::string Book::getInfoValue(int field) const
{
	switch (field) {
	case 0:
		return title;
	case 1:
		return author;
	case 2:
		return description;
	default:
		return "";
	};
}

void Book::setInfoValue(int field, std::string value)
{
	switch (field) {
	case 0:
		title = value;
		break;
	case 1:
		author = value;
		break;
	case 2:
		description = value;
		break;
	default:
		break;
	};
}