#include "Member.h"

#include "Util.h"
#include "Item.h"
#include "Library.h"

Member::Member(std::string username, std::string password) : User(Util::makeFileSafe(Library::INSTANCE->getUserFilenamePrefix() + username) + ".txt")
{
	this->username = username;
	this->password = password;
}

Member::Member(std::string filename, std::ifstream& file) : User(filename)
{
	std::getline(file, username);
	std::getline(file, password);
}

int Member::getType() const
{
	return 0;
}

void Member::saveData(std::ofstream& file)
{
	file << "member\n";
	file << username << "\n";
	file << password << "\n";
}

void Member::resetBorrowedCache()
{
	borrowed.clear();
	reserved.clear();
}

void Member::addBorrowedCache(Item* item)
{
	borrowed.push_back(item);
}

void Member::addReservedCache(Item* item)
{
	reserved.push_back(item);
}

bool Member::loopUI()
{
	int option = Util::getOption({ "View Books", "Current Books", "Account Info"}, "Log Out");

	if (option == 1) {
		Item* item = Library::INSTANCE->searchItem(0);
		if (item != nullptr) {
			std::cout << "\n" << item->getListDisplay() << "\n" << item->getDescription();

			Item::State state = item->getState();
			if (state == Item::State::Available) {
				int choice = Util::getOption({ "Borrow" });
				if (choice == 1) {
					item->borrow(username);
				}
			}
			else if (state == Item::State::Borrowed) {
				int choice = Util::getOption({ "Reserve" });
				if (choice == 1) {
					item->reserve(username);
				}
			}
			else {
				std::cout << "Book Unavailable";
				Util::awaitEnter();
			}
		}
	}
	else if (option == 2) {
		std::vector<std::string> itemNames(borrowed.size()+reserved.size());
		if (itemNames.size() == 0) {
			std::cout << "No Books borrowed or Reserved";
			Util::awaitEnter();
		}
		else {
			std::vector<Item*> items(itemNames.size());
			int i = 0;
			for (Item* borrowedItem : borrowed) {
				items[i] = borrowedItem;
				itemNames[i] = borrowedItem->getListDisplay();
				i++;
			}
			for (Item* reservedItem : reserved) {
				items[i] = reservedItem;
				itemNames[i] = reservedItem->getListDisplay();
				i++;
			}

			int itemIndex = Util::getOption(itemNames);
			if (itemIndex > 0) {
				Item* item = items[itemIndex-1];

				if (itemIndex <= borrowed.size()) {
					if (Util::getOption({ "Return" }) == 1) {
						item->returnItem(username);
					}
				}
				else if (item->getBorrower() == "") {
					int action = Util::getOption({ "Collect Reservation", "Cancel Reservation" });
					if (action == 1) {
						item->borrow(username);
					}
					else if (action == 2) {
						item->returnItem(username);
					}
				}
				else if (Util::getOption({ "Cancel Reservation" }) == 1) {
					item->returnItem(username);
				}
			}
		}
	}
	else if (option == 3) {
		return accountInfoUI(false);
	}

	return option != 0;
}
