#include "Librarian.h"

#include "Util.h"
#include "Library.h"

Librarian::Librarian(std::string username, std::string password) : User(Util::makeFileSafe(Library::INSTANCE->getUserFilenamePrefix() + username))
{
	this->username = username;
	this->password = password;
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

bool Librarian::loopUI()
{
	std::cout << "librarian!!!\n";

	int option = Util::getOption({ "Manage Book", "Account Info"}, "Log Out");

	if (option == 1) {
		Item* item = Library::INSTANCE->searchItem(0);
		if (item != nullptr) {
			std::cout << Util::SAVE_CURSOR_POS;
			int action;
			do {
				std::cout << Util::LOAD_CURSOR_POS << Util::CLEAR_ALL_AFTER << "\n" << item->getListDisplay() << "\n" << item->getDescription() << "\n";
				action = Util::getOption({ "Change Info" });
				if (action == 1) {
					changeInfo(item);
				}
			} while (action > 0);
		}
	}
	else if (option == 2) {
		accountInfoUI();
	}

	return option != 0;
}
