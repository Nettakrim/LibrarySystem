#pragma once
#include<string>
#include <fstream>
#include <iostream>

class Item {
public:
	Item(std::string filename);

	std::string getFilename();

	virtual void saveData(std::ofstream& file) = 0;

	enum State {
		Available,
		Borrowed,
		Reserved,
		Unavailable //"catch all" state for any non-specified reason an item may not be available
	};

	virtual std::string getDescription() = 0;

	void setState(State state);

private:
	std::string filename;

	Item::State state = Available;
};