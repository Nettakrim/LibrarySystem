#include "Member.h"

#include "Util.h"
#include "Item.h"
#include "Library.h"

Member::Member(std::string filename, std::string username, std::string password) : User(filename)
{
	this->username = username;
	this->password = password;
}

Member::Member(std::string filename, std::ifstream& file) : User(filename)
{
	std::getline(file, username);
	std::getline(file, password);
}

void Member::saveData(std::ofstream& file)
{
	file << "member\n";
	file << username << "\n";
	file << password << "\n";
}

bool Member::loopUI()
{
	std::cout << "member!!!\n";

	int option = Util::getOption({ "Borrow" }, "Log Out");

	if (option == 1) {
		Item* item = Library::INSTANCE->searchItem(0);
		if (item != nullptr) {
			std::cout << "\n" << item->getListDisplay() << "\n" << item->getDescription();
			Util::awaitEnter();
		}
	}

	return option != 0;
}
