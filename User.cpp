#include "User.h"

User::User(std::string filename)
{
	this->filename = filename;
}

std::string User::getFilename()
{
	return filename;
}

bool User::loginMatches(std::string username, std::string password) const
{
	return this->username == username && this->password == password;
}
