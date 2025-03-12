#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "Member.h"

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

	State getState() const;

	void borrow(std::string member);

	void reserve(std::string member);

	void setAvailable(bool available);

	void updateBorrowing(time_t currentTime);

	virtual std::string getListDisplay() const = 0;

	virtual std::string getDescription() const = 0;

	virtual std::vector<std::string> getInfoFields() const = 0;

	virtual std::string getInfoValue(int field) const = 0;

	virtual void setInfoValue(int field, std::string value) = 0;

private:
	std::string filename;

protected:
	Item::State state = Available;

	time_t dueAt = 0;

	std::string borrowedBy = "";
	std::string reservedBy = "";
};