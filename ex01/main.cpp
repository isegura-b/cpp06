#include <iostream>
#include "Serializer.hpp"

int main()
{
    Data original;
    original.value = 42;
    original.text = "Hola";

    std::cout << "Original pointer: " << &original << std::endl;
    std::cout << "Original content: " << original.value << ", " << original.text << std::endl;
    uintptr_t raw = Serializer::serialize(&original);
    std::cout << "Raw serialized: " << raw << std::endl;
    Data *restored = Serializer::deserialize(raw);
    std::cout << "Restored pointer == original ? " << std::endl;
    if (restored == &original)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    std::cout << "Restored content: "
              << restored->value << ", " << restored->text << std::endl;

    return 0;
}
