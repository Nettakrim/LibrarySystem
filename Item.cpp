#include<string>
#include "Item.h"

Item::Item(std::string filename)
{
	this->filename = filename;
}

void Item::setState(State state)
{
	this->state = state;
}

std::string Item::getFilename()
{
	return filename;
}
