#include <iostream>

#include "Library.h"

int main()
{
    Library* library = new Library();

    std::string username;
    std::string password;
    while (true) {
        std::cout << "enter username: ";
        std::cin >> username;
        std::cin.ignore();
        std::cout << "enter password: ";
        std::cin >> password;
        std::cin.ignore();

        User* user = library->tryLogin(username, password);
        if (user == nullptr) {
            std::cout << "invalid username or password\n";
            break;
        }

        user->openUI();
    }

    delete library;
    std::cout << "\npress ENTER to close...";
    std::cin.ignore();
}