#pragma once
#include "Item.h"

class Book : public Item {
public:
	Book(std::string filename);

	~Book();

	std::string getDescription();

	Book(std::string filename, std::ifstream& file);

	void saveData(std::ofstream& file);
};