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

	dir.append("/data/UUID.txt");
	std::ifstream file(dir);
	file >> usersUUID;
	file >> itemsUUID;
}

void Library::save()
{
	std::string dir = std::filesystem::current_path().string();

	for (Item* item : items) {
		std::string path = dir;
		path.append(itemDir).append(item->getFilename());
		std::ofstream file(path);
		item->saveData(file);
		file.close();
	}

	for (User* user : users) {
		std::string path = dir;
		path.append(userDir).append(user->getFilename());
		std::ofstream file(path);
		user->saveData(file);
		file.close();
	}

	std::ofstream file(dir.append("/data/UUID.txt"));
	file << usersUUID << "\n";
	file << itemsUUID << "\n";
	file.close();
}

std::string Library::getUserFilenamePrefix() const
{
	return std::to_string(usersUUID) + " ";
}

std::string Library::getItemFilenamePrefix() const
{
	return std::to_string(itemsUUID) + " ";
}