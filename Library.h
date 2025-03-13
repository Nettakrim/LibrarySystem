#pragma once

#include <list>

#include "Item.h"
#include "User.h"

class Library {
private:
	std::list<User*> users;
	std::list<Item*> items;

	unsigned long usersUUID;
	unsigned long itemsUUID;

public:
	static Library* INSTANCE;

	std::list<std::string*> unapprovedActions;

	Library();

	~Library();

	void save();

	void load();

	std::string getUserFilenamePrefix() const;

	std::string getItemFilenamePrefix() const;

	void addUser(User* user);

	void removeUser(User* user);

	void addItem(Item* item);

	void removeItem(Item* item);

	User* getUser(std::string username);

	std::list<Item*> getItems(int type);

	Item* searchItem(int type);

	void updateBorrowing();

	User* getUserByFilename(std::string filename) const;

	Item* getItemByFilename(std::string filename) const;

	int borrowDuration;

	int reservationDuration;

	int maxClaims;
};