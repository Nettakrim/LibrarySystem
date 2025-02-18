#pragma once
#include<string>

class Item {
public:
	enum State {
		Available,
		Borrowed,
		Reserved,
		Unavailable //"catch all" state for any non-specified reason an item may not be available
	};

	virtual std::string getDescription() = 0;

	void setState(State state);

private:
	Item::State state = Available;
};