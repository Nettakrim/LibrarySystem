#include "Librarian.h"

#include "Util.h"
#include "Library.h"
#include "Book.h"

Librarian::Librarian(std::string username, std::string password) : User(Util::makeFileSafe(Library::INSTANCE->getUserFilenamePrefix() + username) + ".txt")
{
	this->username = username;
	this->password = password;
}

Librarian::Librarian(std::string filename, std::ifstream& file) : User(filename)
{
	std::getline(file, username);
	std::getline(file, password);
}

int Librarian::getType() const
{
	return 1;
}

void Librarian::saveData(std::ofstream& file)
{
	file << "librarian\n";
	file << username << "\n";
	file << password << "\n";
}

void changeInfo(Item* item) {
	int field = Util::getOption(item->getInfoFields());
	if (field == 0) {
		return;
	}
	field--;

	std::cout << "\nCurrent Value: " + item->getInfoValue(field);
	std::cout << "\nNew Value:     ";

	std::string value;
	std::getline(std::cin, value);
	item->setInfoValue(field, value);

	std::cout << "Updated";
	Util::awaitEnter();
}

void manageItem(Item* item) {
	std::cout << Util::SAVE_CURSOR_POS;
	int action;
	do {
		std::cout << Util::LOAD_CURSOR_POS << Util::CLEAR_ALL_AFTER << "\n" << item->getListDisplay() << "\n" << item->getDescription() << "\n";
		action = Util::getOption({ "Change Info", "Force-set availability", "Remove from Library"});
		if (action == 1) {
			changeInfo(item);
		}
		else if (action == 2) {
			int available = Util::getOption({ "Available", "Unavailable"});
			if (available > 0) {
				item->setAvailable(available == 1);
			}
		}
		else if (action == 3) {
			Library::INSTANCE->removeItem(item);
			std::cout << "Item Removed";
			Util::awaitEnter();
			return;
		}
	} while (action > 0);
}

bool approvalUI() {
	std::vector<User*> approvalUsers;
	std::vector<std::string> approvalActions;
	std::vector<Item*> approvalItems;

	std::list<std::string*> invalid;

	for (std::string* action : Library::INSTANCE->unapprovedActions) {
		User* user = Library::INSTANCE->getUserByFilename(action[0]);
		std::string type = action[1];
		Item* item = Library::INSTANCE->getItemByFilename(action[2]);

		if (user != nullptr && item != nullptr) {
			if ((type == "borrow" && item->getBorrower() == user->getUsername()) || (type == "reserve" && item->getReserver() == user->getUsername())) {
				approvalUsers.push_back(user);
				approvalActions.push_back(type);
				approvalItems.push_back(item);
				continue;
			}
		}

		invalid.push_back(action);
	}

	for (std::string* invalidAction : invalid) {
		Library::INSTANCE->unapprovedActions.remove(invalidAction);
	}

	if (approvalUsers.size() == 0) {
		std::cout << "No unprocessed requests";
		Util::awaitEnter();
		return false;
	}

	std::vector<std::string> approvalOptions(approvalUsers.size());
	for (int i = 0; i < approvalUsers.size(); i++) {
		approvalOptions[i] = approvalUsers[i]->getUsername() + " " + approvalActions[i] + "ing " + approvalItems[i]->getInfoValue(0);
	}

	std::cout << Util::SAVE_CURSOR_POS;
	while (true) {
		std::cout << Util::LOAD_CURSOR_POS << Util::CLEAR_ALL_AFTER;
		int request = Util::getOption(approvalOptions);
		if (request == 0) {
			return false;
		}
		request--;

		int choice = Util::getOption({ "Approve", "Deny" });
		if (choice == 0) {
			continue;
		}

		if (choice == 2) {
			approvalItems[request]->returnItem(approvalUsers[request]->getUsername());
		}

		auto x = Library::INSTANCE->unapprovedActions.begin();
		std::advance(x, request);
		Library::INSTANCE->unapprovedActions.erase(x);
		std::cout << Util::LOAD_CURSOR_POS << Util::CLEAR_ALL_AFTER;

		return true;
	}
}

bool Librarian::loopUI()
{
	if (Library::INSTANCE->unapprovedActions.size() > 0) {
		std::cout << "Requests need to be approved\n";
	}

	int option = Util::getOption({ "Manage Book", "Add Book", "Manage Requests", "Generate Report", "Account Info"}, "Log Out");;

	if (option == 1) {
		Item* item = Library::INSTANCE->searchItem(0);
		if (item != nullptr) {
			manageItem(item);
		}
	}
	else if (option == 2) {
		std::string title = Util::getStringInput("Enter Title", true);
		if (title != "") {
			Item* item = new Book(title);
			Library::INSTANCE->addItem(item);
			manageItem(item);
		}
		else {
			std::cout << "Book Addition Cancelled";
			Util::awaitEnter();
		}
	}
	else if (option == 3) {
		do {} while (approvalUI());
	}
	else if (option == 4) {
		int type = Util::getOption({ "Borrowed Books", "Overdue Books" });
		if (type > 0) {
			std::cout << Util::CLEAR_ALL;
			Library::INSTANCE->printReport(type - 1);
			Util::awaitEnter();
		}
	}
	else if (option == 5) {
		return accountInfoUI(false);
	}

	return option != 0;
}
