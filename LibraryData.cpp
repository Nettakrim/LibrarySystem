#include "Library.h"

#include <filesystem> 
#include <fstream> 
#include <iostream> 
#include <string>

#include "Item.h"
#include "Book.h"

void Library::load()
{
	std::string dir = std::filesystem::current_path().string();

	std::string line;

	std::string path = dir.append("/data/items");
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		std::filesystem::path path = entry.path();

		std::ifstream file(path);

		while (std::getline(file, line)) {
			std::cout << line;
		}

		std::cout << std::endl;

		file.close();

		items.push_back(new Book(path.filename().string()));
	}
}

void Library::save()
{
	std::string dir = std::filesystem::current_path().string();

	for (Item* item : items) {
		std::ofstream file(dir.append("/data/items/").append(item->getFilename()));

		file << "test";

		file.close();
	}
}