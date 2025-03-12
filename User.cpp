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
	std::cout << "\n" << username;

	int option = Util::getOption({ "Delete Account" });

	if (option == 1) {
		if (Util::getOption({ "Confirm Delete" }) != 0) {
			Library::INSTANCE->removeUser(this);
			std::cout << "Account Deleted Successfully";
			Util::awaitEnter();
			return false;
		}
	}

	return true;
}
