#include "Administrator.h"

#include "Util.h"
#include "Library.h"
#include "Librarian.h"

Administrator::Administrator(std::string username, std::string password) : User(Util::makeFileSafe(Library::INSTANCE->getUserFilenamePrefix() + username))
{
	this->username = username;
	this->password = password;
}

Administrator::Administrator(std::string filename, std::ifstream& file) : User(filename)
{
	std::getline(file, username);
	std::getline(file, password);
}

void Administrator::saveData(std::ofstream& file)
{
	file << "administrator\n";
	file << username << "\n";
	file << password << "\n";
}

bool Administrator::loopUI()
{
	std::cout << "admin!!!\n";
	
	int option = Util::getOption({ "Create New Account", "Delete Account" }, "Log Out");

	if (option == 1) {
		int type = Util::getOption({ "Librarian", "Admin" });
		if (type != 0) {
			std::string username;
			std::string password;
			std::cout << "Enter Username: ";
			std::getline(std::cin, username);
			std::cout << "Enter Password: ";
			std::getline(std::cin, password);

			User* user = Library::INSTANCE->getUser(username);
			if (user != nullptr) {
				std::cout << "User \"" << username << "\" already exists";
				Util::awaitEnter();
			}
			else {
				User* user = type == 1 ? (User*)new Librarian(username, password) : (User*)new Administrator(username, password);
				Library::INSTANCE->addUser(user);
				std::cout << "User Created Successfully";
				Util::awaitEnter();
			}
		}
	}
	else if (option == 2) {
		std::string username;
		std::cout << "Enter Username of account to Delete: ";
		std::getline(std::cin, username);
		User* user = Library::INSTANCE->getUser(username);
		if (user == nullptr) {
			std::cout << "No User " << user << " found";
			Util::awaitEnter();
		}
		else {
			if (Util::getOption({ "Confirm" }) != 0) {
				Library::INSTANCE->removeUser(user);
				std::cout << "User Deleted Successfully";
				Util::awaitEnter();
			}
		}
	}

	return option != 0;
}
