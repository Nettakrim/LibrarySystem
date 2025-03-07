#pragma once
#include "User.h"

class Librarian : public User {
public:
	Librarian(std::string filename, std::ifstream& file);

	void saveData(std::ofstream& file);

	void openUI();
};