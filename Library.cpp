#include "Library.h"

Library* Library::INSTANCE;

Library::Library() {
	Library::INSTANCE = this;

	load();
}

Library::~Library()
{
	save();
}

User* Library::tryLogin(std::string username, std::string password)
{
	for (User* user : users) {
		if (user->loginMatches(username, password)) {
			return user;
		}
	}
	return nullptr;
}