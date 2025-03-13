#include "Library.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Item.h"
#include "Book.h"

#include "User.h"
#include "Member.h"
#include "Librarian.h"
#include "Administrator.h"

const std::string itemDir = "/data/items/";
const std::string userDir = "/data/users/";

void Library::load()
{
	std::string dir = std::filesystem::current_path().string();

	std::string line;

	std::string folder = dir;
	for (const auto& entry : std::filesystem::directory_iterator(folder.append(userDir))) {
		std::filesystem::path path = entry.path();

		std::ifstream file(path);

		if (std::getline(file, line)) {
			std::string filename = path.filename().string();
			if (line == "member") {
				users.push_back(new Member(filename, file));
			}
			else if (line == "librarian") {
				users.push_back(new Librarian(filename, file));
			}
			else if (line == "administrator") {
				users.push_back(new Administrator(filename, file));
			}
		}

		file.close();
	}

	folder = dir;
	for (const auto& entry : std::filesystem::directory_iterator(folder.append(itemDir))) {
		std::filesystem::path path = entry.path();

		std::ifstream file(path);

		if (std::getline(file, line)) {
			std::string filename = path.filename().string();
			if (line == "book") {
				items.push_back(new Book(filename, file));
			}
		}

		file.close();
	}

	folder = dir;
	std::ifstream file1(folder.append("/data/UUID.txt"));
	file1 >> usersUUID;
	file1 >> itemsUUID;
	file1.close();

	folder = dir;
	std::ifstream file2(folder.append("/data/UnapprovedActions.txt"));

	std::string user;
	std::string action;
	std::string item;
	int i;
	while (std::getline(file2, line)) {
		i = line.find('/');
		user = line.substr(0, i);
		action = line.substr(i + 1);
		i = action.find('/');
		item = action.substr(i + 1);
		action = action.substr(0, i);

		std::string* s = new std::string[3];
		s[0] = user;
		s[1] = action;
		s[2] = item;
		unapprovedActions.push_back(s);
	}
	file2.close();
}

void Library::save()
{
	std::string dir = std::filesystem::current_path().string();

	for (User* user : users) {
		std::string path = dir;
		path.append(userDir).append(user->getFilename());
		std::ofstream file(path);
		user->saveData(file);
		file.close();
	}

	for (Item* item : items) {
		std::string path = dir;
		path.append(itemDir).append(item->getFilename());
		std::ofstream file(path);
		item->saveData(file);
		file.close();
	}

	std::string path = dir;
	std::ofstream file1(path.append("/data/UUID.txt"));
	file1 << usersUUID << "\n";
	file1 << itemsUUID << "\n";
	file1.close();

	path = dir;
	std::ofstream file2(path.append("/data/UnapprovedActions.txt"));
	for (std::string* action : unapprovedActions) {
		file2 << action[0] << "/" << action[1] << "/" << action[2] << "\n";
	}
	file2.close();
}

std::string Library::getUserFilenamePrefix() const
{
	return std::to_string(usersUUID) + " ";
}

std::string Library::getItemFilenamePrefix() const
{
	return std::to_string(itemsUUID) + " ";
}

void Library::removeUser(User* user)
{
	users.remove(user);
	std::remove(std::filesystem::current_path().string().append(userDir).append(user->getFilename()).c_str());
}

void Library::removeItem(Item* item)
{
	items.remove(item);
	std::remove(std::filesystem::current_path().string().append(itemDir).append(item->getFilename()).c_str());
}
