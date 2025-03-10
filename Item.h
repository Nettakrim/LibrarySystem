#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Item {
public:
	Item(std::string filename);

	std::string getFilename() const;

	virtual int getType() const = 0;

	virtual void saveData(std::ofstream& file) = 0;

	enum State {
		Available,
		Borrowed,
		Reserved,
		Unavailable //"catch all" state for any non-specified reason an item may not be available
	};

	static std::string getStateName(State state);

	void setState(State state);

	State getState() const;

	virtual std::string getListDisplay() const = 0;

	virtual std::string getDescription() const = 0;

	virtual std::vector<std::string> getInfoFields() const = 0;

	virtual std::string getInfoValue(int field) const = 0;

private:
	std::string filename;

	Item::State state = Available;
};