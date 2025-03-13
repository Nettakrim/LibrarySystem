#pragma once
#include "User.h"
#include "Item.h"

#include <list>

class Member : public User {
private:
	std::list<Item*> borrowed;
	std::list<Item*> reserved;
	std::list<Item*> overdue;

public:
	Member(std::string username, std::string password);

	Member(std::string filename, std::ifstream& file);

	int getType() const;

	void saveData(std::ofstream& file);

	void resetBorrowedCache();

	void addBorrowedCache(Item* item);

	void addReservedCache(Item* item);

	void addOverdueCache(Item* item);

	bool loopUI();
};