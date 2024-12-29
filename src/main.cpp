#include <iostream>
#include "material.h"

int main() {
    using namespace heat;

    // Print predefined materials
    std::cout << "Available Materials:\n\n";
    std::cout << copper << "\n";
    std::cout << iron << "\n";
    std::cout << glass << "\n";
    std::cout << polystyrene << "\n";

    // Example of a custom material
    Material customMaterial("Custom Material", 50.0, 5000.0, 400.0);
    std::cout << "\nCustom Material:\n" << customMaterial << "\n";

    return 0;
}
