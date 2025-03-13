#include "User.h"

#include "Util.h"
#include "Library.h"

User::User(std::string filename)
{
	this->filename = filename;
}

std::string User::getFilename()
{
	return filename;
}

bool User::usernameMatches(std::string username) const
{
	return this->username == username;
}

bool User::passwordMatches(std::string password) const
{
	return this->password == password;
}

bool User::accountInfoUI(bool admin)
{
	std::cout << Util::SAVE_CURSOR_POS;

	int option;
	do {
		std::cout << Util::LOAD_CURSOR_POS << Util::CLEAR_ALL_AFTER << "\n";
		std::cout << "Username: " << username << "\n";

		option = Util::getOption({ "Update Password", "Delete Account" });

		if (option == 1) {
			if (!admin) {
				std::string password;
				std::cout << "Enter Current Password: ";
				std::getline(std::cin, password);
				if (!passwordMatches(password)) {
					std::cout << "Invalid Password";
					Util::awaitEnter();
					continue;
				}
			}

			this->password = Util::getStringInput("Enter New Password", false);
			std::cout << "Updated Password";
			Util::awaitEnter();
		}
		else if (option == 2) {
			if (Util::getOption({ "Confirm Delete" }) != 0) {
				Library::INSTANCE->removeUser(this);
				std::cout << "Account Deleted Successfully";
				Util::awaitEnter();
				return false;
			}
		}

	} while (option > 0);
	return true;
}

std::string User::getUsername()
{
	return username;
}
