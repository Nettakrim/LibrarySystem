#pragma once
#include "Item.h"

class Book : public Item {
public:
	Book();

	~Book();

	std::string getDescription();
};