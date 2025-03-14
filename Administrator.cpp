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
	int option = Util::getOption({ "Create New Account", "Manage Account", "Set Setting"}, "Log Out");

	if (option == 1) {
		int type = Util::getOption({ "Librarian", "Admin" });
		if (type != 0) {
			std::string username = Util::getStringInput("Enter Username", true);
			if (username == "" || username == "/") {
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
	else if (option == 3) {
		int choice = Util::getOption({ "Borrow Duration", "Reservation Duration", "Max Claims" });
		if (choice > 0) {
			std::cout << "Current Value: ";
			if (choice == 1) {
				std::cout << Library::INSTANCE->borrowDuration;
			}
			else if (choice == 2) {
				std::cout << Library::INSTANCE->reservationDuration;
			}
			else if (choice == 3) {
				std::cout << Library::INSTANCE->maxClaims;
			}
			std::cout << "\n";
			int i = std::atoi(Util::getStringInput("New Value", false).c_str());
			if (choice == 1) {
				Library::INSTANCE->borrowDuration = i;
			}
			else if (choice == 2) {
				Library::INSTANCE->reservationDuration = i;
			}
			else if (choice == 3) {
				Library::INSTANCE->maxClaims = i;
			}
		}
	}

	return option != 0;
}
