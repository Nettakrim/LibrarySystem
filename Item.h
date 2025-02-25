#pragma once
#include<string>

class Item {
public:
	Item(std::string filename);

	enum State {
		Available,
		Borrowed,
		Reserved,
		Unavailable //"catch all" state for any non-specified reason an item may not be available
	};

	virtual std::string getDescription() = 0;

	void setState(State state);

	std::string getFilename();

private:
	Item::State state = Available;

	std::string filename;
};