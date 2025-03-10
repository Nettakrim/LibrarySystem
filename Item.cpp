#include<string>
#include "Item.h"

Item::Item(std::string filename)
{
	this->filename = filename;
}

std::string Item::getStateName(State state)
{
	switch (state) {
	case Item::Available:
		return "Available";
	case Item::Borrowed:
		return "Borrowed";
	case Item::Reserved:
		return "Reserved";
	case Item::Unavailable:
		return "Unavailable";
	};
}

void Item::setState(State state)
{
	this->state = state;
}

Item::State Item::getState() const
{
	return this->state;
}

std::string Item::getFilename() const
{
	return filename;
}
