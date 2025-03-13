#include "Librarian.h"

#include "Util.h"
#include "Library.h"
#include "Book.h"

Librarian::Librarian(std::string username, std::string password) : User(Util::makeFileSafe(Library::INSTANCE->getUserFilenamePrefix() + username) + ".txt")
{
	this->username = username;
	this->password = password;
}

Librarian::Librarian(std::string filename, std::ifstream& file) : User(filename)
{
	std::getline(file, username);
	std::getline(file, password);
}

int Librarian::getType() const
{
	return 1;
}

void Librarian::saveData(std::ofstream& file)
{
	file << "librarian\n";
	file << username << "\n";
	file << password << "\n";
}

void changeInfo(Item* item) {
	int field = Util::getOption(item->getInfoFields());
	if (field == 0) {
		return;
	}
	field--;

	std::cout << "\nCurrent Value: " + item->getInfoValue(field);
	std::cout << "\nNew Value:     ";

	std::string value;
	std::getline(std::cin, value);
	item->setInfoValue(field, value);

	std::cout << "Updated";
	Util::awaitEnter();
}

void manageItem(Item* item) {
	std::cout << Util::SAVE_CURSOR_POS;
	int action;
	do {
		std::cout << Util::LOAD_CURSOR_POS << Util::CLEAR_ALL_AFTER << "\n" << item->getListDisplay() << "\n" << item->getDescription() << "\n";
		action = Util::getOption({ "Change Info", "Remove from Library"});
		if (action == 1) {
			changeInfo(item);
		}
		else if (action == 2) {
			Library::INSTANCE->removeItem(item);
			std::cout << "Item Removed";
			Util::awaitEnter();
			return;
		}
	} while (action > 0);
}

bool Librarian::loopUI()
{
	int option = Util::getOption({ "Manage Book", "Add Book", "Account Info"}, "Log Out");

	if (option == 1) {
		Item* item = Library::INSTANCE->searchItem(0);
		if (item != nullptr) {
			manageItem(item);
		}
	}
	else if (option == 2) {
		std::string title = Util::getStringInput("Enter Title", true);
		if (title != "") {
			Item* item = new Book(title);
			Library::INSTANCE->addItem(item);
			manageItem(item);
		}
		else {
			std::cout << "Book Addition Cancelled";
			Util::awaitEnter();
		}
	}
	else if (option == 3) {
		return accountInfoUI(false);
	}

	return option != 0;
}
