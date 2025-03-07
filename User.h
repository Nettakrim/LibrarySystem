#pragma once
#include <fstream>
#include <iostream>
#include <string>

class User {
public:
	User(std::string filename);

	std::string getFilename();

	virtual void saveData(std::ofstream& file) = 0;

	bool loginMatches(std::string username, std::string password);

	virtual void openUI() = 0;
private:
	std::string filename;

protected:
	std::string username;
	std::string password;
};