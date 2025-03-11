#pragma once
#include "User.h"

class Administrator : public User {
public:
	Administrator(std::string username, std::string password);

	Administrator(std::string filename, std::ifstream& file);

	void saveData(std::ofstream& file);

	bool loopUI();
};