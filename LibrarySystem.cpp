#include <iostream>

#include "Library.h"

int main()
{
    Library* library = new Library();

    std::cin.ignore();
    delete library;
}