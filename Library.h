#pragma once

#include <list>
#include "Item.h"
#include "User.h"

class Library {
private:
	std::list<Item*> items;
	std::list<User*> users;

public:
	static Library* INSTANCE;

	Library();

	~Library();

	void save();

	void load();
};