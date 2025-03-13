#include "Item.h"

#include <string>

#include "User.h"
#include "Member.h"
#include "Util.h"
#include "Library.h"

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
	return "???";
}

Item::State Item::getState() const
{
	return this->state;
}

void Item::borrow(std::string member)
{
	borrowedBy = member;
	dueAt = Util::getUnixTime() + (5 * 24 * 60 * 60);

	reservedBy = "";
	state = State::Borrowed;
}

void Item::reserve(std::string member)
{
	reservedBy = member;
	state = State::Reserved;
}

void Item::returnItem(std::string member)
{
	if (borrowedBy == member) {
		borrowedBy = "";
		if (state == State::Reserved) {
			dueAt = Util::getUnixTime() + 3 * 24 * 60 * 60;
		}
	}
	else if (reservedBy == member) {
		reservedBy = "";
	}
	updateBorrowing(0);
}

std::string Item::getBorrower() const
{
	return borrowedBy;
}

std::string Item::getReserver() const
{
	return reservedBy;
}

void Item::setAvailable(bool available)
{
	state = available ? State::Available : State::Unavailable;
}

static Member* tryGetMember(std::string name) {
	if (name != "") {
		User* user = Library::INSTANCE->getUser(name);
		if (user->getType() == 0) {
			return (Member*)user;
		}
	}
	return nullptr;
}

void Item::updateBorrowing(time_t currentTime) {
	Member* borrower = tryGetMember(borrowedBy);
	Member* reserver = tryGetMember(reservedBy);

	if (borrower == nullptr) {
		borrowedBy = "";
	}
	if (reserver == nullptr) {
		reservedBy = "";
		if (borrower == nullptr) {
			if (state != State::Unavailable) {
				state = State::Available;
			}
			return;
		}
	}

	if (borrowedBy == "" && state == State::Borrowed) {
		state = State::Available;
	}
	if (reservedBy == "" && state == State::Reserved) {
		state = borrowedBy == "" ? State::Available : State::Borrowed;
	}

	
	if (dueAt < currentTime) {
		if (borrowedBy != "") {
			if (currentTime > 0) {
				borrower->addOverdueCache(this);
			}
		} else if (reservedBy != "") {
			state = State::Available;
			reservedBy = "";
		}
	}

	if (currentTime > 0) {
		if (borrowedBy != "") {
			borrower->addBorrowedCache(this);
		}
		if (reservedBy != "") {
			reserver->addReservedCache(this);
		}
	}
}

std::string Item::getFilename() const
{
	return filename;
}
