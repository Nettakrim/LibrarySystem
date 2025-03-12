#pragma once
#include <fstream>
#include <iostream>
#include <string>

class User {
public:
	User(std::string filename);

	std::string getFilename();

	virtual void saveData(std::ofstream& file) = 0;

	bool usernameMatches(std::string username) const;

	bool passwordMatches(std::string password) const;

	virtual bool loopUI() = 0;

	bool accountInfoUI(bool admin);
private:
	std::string filename;

protected:
	std::string username;
	std::string password;
};