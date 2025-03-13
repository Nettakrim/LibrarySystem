#include "Administrator.h"

#include "Util.h"
#include "Library.h"
#include "Librarian.h"

Administrator::Administrator(std::string username, std::string password) : User(Util::makeFileSafe(Library::INSTANCE->getUserFilenamePrefix() + username) + ".txt")
{
	this->username = username;
	this->password = password;
}

Administrator::Administrator(std::string filename, std::ifstream& file) : User(filename)
{
	std::getline(file, username);
	std::getline(file, password);
}

int Administrator::getType() const
{
	return 2;
}

void Administrator::saveData(std::ofstream& file)
{
	file << "administrator\n";
	file << username << "\n";
	file << password << "\n";
}

bool Administrator::loopUI()
{
	int option = Util::getOption({ "Create New Account", "Manage Account"}, "Log Out");

	if (option == 1) {
		int type = Util::getOption({ "Librarian", "Admin" });
		if (type != 0) {
			std::string username = Util::getStringInput("Enter Username", true);
			if (username == "") {
				std::cout << "Cancelled";
				Util::awaitEnter();
			}
			else {
				std::string password = Util::getStringInput("Enter Password", false);

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
	}
	else if (option == 2) {
		std::string username = Util::getStringInput("Enter Username", true);
		User* user = Library::INSTANCE->getUser(username);
		if (user == nullptr) {
			std::cout << "No User " << user << " found";
			Util::awaitEnter();
		}
		else {
			bool isThis = username == this->username;
			if (!user->accountInfoUI(!isThis) && isThis) {
				return false;
			}
		}
	}

	return option != 0;
}
