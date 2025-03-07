#include <iostream>

#include "Library.h"
#include "Util.h"

static void mainLoop() {
    while (true) {
        std::cout << Util::CLEAR_ALL;
        int loop = Util::getOption({ "Login" }, "Exit");

        if (loop == 0) {
            return;
        }

        std::string username;
        std::string password;
        std::cout << "Enter Username: ";
        std::getline(std::cin, username);
        std::cout << "Enter Password: ";
        std::getline(std::cin, password);

        User* user = Library::INSTANCE->tryLogin(username, password);
        if (user == nullptr) {
            std::cout << "Invalid Username or Password\n";
            Util::awaitEnter();
            continue;
        }

        std::cout << Util::CLEAR_ALL;
        while (user->loopUI()) {
            std::cout << Util::CLEAR_ALL;
        }
    }
}

int main()
{
    Library* library = new Library();

    mainLoop();

    delete library;
}