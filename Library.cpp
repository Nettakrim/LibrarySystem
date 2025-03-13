#include "Library.h"

#include "Util.h"
#include "Member.h"

#include <vector>

Library* Library::INSTANCE;

Library::Library() {
	Library::INSTANCE = this;

	load();
}

Library::~Library()
{
	save();
}

void Library::addUser(User* user)
{
	users.push_back(user);
	usersUUID++;
}

void Library::addItem(Item* item)
{
	items.push_back(item);
	itemsUUID++;
}

User* Library::getUser(std::string username)
{
	for (User* user : users) {
		if (user->usernameMatches(username)) {
			return user;
		}
	}
	return nullptr;
}

std::list<Item*> Library::getItems(int type)
{
	std::list<Item*> items = std::list<Item*>();
	for (Item* item : this->items) {
		if (item->getType() == type) {
			items.push_back(item);
		}
	}
	return items;
}

Item* Library::searchItem(int type)
{
	std::list<Item*> items = Library::INSTANCE->getItems(type);

	if (items.empty()) {
		return nullptr;
	}

	int i;
	int searchField;
	std::vector<Item*> matches(items.size());
	std::string searchText;
	std::string field;

	std::vector<std::string> fieldNames = items.front()->getInfoFields();

	std::cout << "Search By:\n";
	while (true) {
		searchField = Util::getOption(fieldNames);

		if (searchField == 0) {
			return nullptr;
		}
		searchField--;
	
		std::cout << "Search For: ";
		std::getline(std::cin, searchText);
		searchText = Util::toLower(searchText);

		i = 0;
		for (Item* item : items) {
			field = Util::toLower(item->getInfoValue(searchField));

			if (field.find(searchText) != std::string::npos) {
				matches[i] = item;
				i++;
			}
		}

		if (i == 0) {
			std::cout << "No Matches";
			Util::awaitEnter();
			Util::moveBackAndClear((int)fieldNames.size() + 3);
			continue;
		}

		std::vector<std::string> matchNames(i);
		i--;
		while (i >= 0) {
			matchNames[i] = matches[i]->getListDisplay();
			i--;
		}

		int item = Util::getOption(matchNames);

		if (item == 0) {
			Util::moveBackAndClear((int)fieldNames.size() + (int)matchNames.size() + 4);
			continue;
		}
		item--;

		return matches[item];
	}
}

void Library::updateBorrowing()
{
	for (User* user : users) {
		if (user->getType() == 0) {
			((Member*)user)->resetBorrowedCache();
		}
	}

	time_t time = Util::getUnixTime();
	for (Item* item : items) {
		item->updateBorrowing(time);
	}
}
