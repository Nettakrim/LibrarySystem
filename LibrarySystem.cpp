#include <iostream>

#include "Library.h"
#include "Util.h"
#include "Member.h"

static void mainLoop() {
    while (true) {
        std::cout << Util::CLEAR_ALL;
        int option = Util::getOption({ "Login", "Create Account"}, "Exit");

        if (option == 0) {
            return;
        }

        std::string username = Util::getStringInput("Enter Username", true);
        if (username == "") {
            std::cout << "Cancelled";
            Util::awaitEnter();
            continue;
        }
        std::string password = Util::getStringInput("Enter Password", option == 1);

        User* user = Library::INSTANCE->getUser(username);
        if (option == 2) {
            if (user != nullptr) {
                std::cout << "User \"" << username << "\" already exists";
                Util::awaitEnter();
                continue;
            }

            user = new Member(username, password);
            Library::INSTANCE->addUser(user);
        }
        else {
            if (user == nullptr || !user->passwordMatches(password)) {
                std::cout << "Invalid Username or Password\n";
                Util::awaitEnter();
                continue;
            }
        }

        Library::INSTANCE->updateBorrowing();

        do {
            std::cout << Util::CLEAR_ALL;
        } while (user->loopUI());
    }
}

int main()
{
    Library* library = new Library();

    mainLoop();

    delete library;
}