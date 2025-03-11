#pragma once
#include "Item.h"

class Book : public Item {
private:
	std::string title;
	std::string author;

public:
	Book(std::string filename);

	int getType() const;

	~Book();

	Book(std::string filename, std::ifstream& file);

	void saveData(std::ofstream& file);

	std::string getListDisplay() const;

	std::string getDescription() const;

	std::vector<std::string> getInfoFields() const;

	std::string getInfoValue(int field) const;

	void setInfoValue(int field, std::string value);
};