#include <iostream>

#include "Book.h"

int main()
{
    std::cout << "Hello World!\n";
    Item* book = new Book();
    std::cout << book->getDescription();

    std::cin.ignore();
}