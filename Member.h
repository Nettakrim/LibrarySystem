#pragma once
#include "User.h"

class Member : public User {
public:
	Member(std::string username, std::string password);

	Member(std::string filename, std::ifstream& file);

	void saveData(std::ofstream& file);

	bool loopUI();
};