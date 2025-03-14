#include "Book.h"

#include "Util.h"
#include "Library.h"

Book::Book(std::string title) : Item(Util::makeFileSafe(Library::INSTANCE->getItemFilenamePrefix() + title) + ".txt")
{
	this->title = title;
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
	file >> dueAt;
	file.ignore();

	std::getline(file, borrowedBy);
	std::getline(file, reservedBy);

	if (borrowedBy == "/" && reservedBy == "/") {
		state = State::Unavailable;
	}
	else if (reservedBy != "") {
		state = State::Reserved;
	}
	else if (borrowedBy != "") {
		state = State::Borrowed;
	}

	std::getline(file, title);
	std::getline(file, author);
	std::getline(file, description);
	std::getline(file, isbn);
}

void Book::saveData(std::ofstream& file)
{
	if (state == State::Unavailable) {
		borrowedBy = "/";
		reservedBy = "/";
	}

	file << "book\n";
	file << dueAt << "\n";
	file << borrowedBy << "\n";
	file << reservedBy << "\n";

	file << title << "\n";
	file << author << "\n";
	file << description << "\n";
	file << isbn << "\n";
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
	return { "Title", "Author", "Description", "ISBN"};
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
	case 3:
		return isbn;
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
	case 3:
		isbn = value;
		break;
	default:
		break;
	};
}