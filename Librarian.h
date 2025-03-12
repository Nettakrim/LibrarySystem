#pragma once
#include "User.h"

class Librarian : public User {
public:
	Librarian(std::string username, std::string password);

	Librarian(std::string filename, std::ifstream& file);

	int getType() const;

	void saveData(std::ofstream& file);

	bool loopUI();
};