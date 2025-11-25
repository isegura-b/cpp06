#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Base.hpp"

Base *generate()
{
    int randNum = std::rand() % 3;      //generate a random number between 0 and 2
    if (randNum == 0)
        return new A();
    else if (randNum == 1)
        return new B();
    else
        return new C();
}

void identify(Base *p)                  //identify the type using pointer
{
    if (dynamic_cast<A *>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B *>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C *>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown Type" << std::endl;
}

void identify(Base &p)                  //identify the type using reference
{
    try
    {
        (void)dynamic_cast<A &>(p);         //if a == clase base
        std::cout << "A" << std::endl;      //else exception(std::bad_cast)
        return;
    }
    catch (...){}                          //catch all exceptions

    try
    {        (void)dynamic_cast<B &>(p);
        std::cout << "B" << std::endl;
        return;
    }
    catch (...){}

    try
    {
        (void)dynamic_cast<C &>(p);
        std::cout << "C" << std::endl;
        return;
    }
    catch (...){}

    std::cout << "Unknown Type" << std::endl;
}

int main()
{
    std::srand(std::time(NULL));

    Base *test = generate();

    std::cout << "Pointer: ";
    identify(test);

    std::cout << "Reference: ";
    identify(*test);

    delete test;
    return 0;
}
