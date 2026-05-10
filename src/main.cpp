#include "../include/Gui.h"
#include "../include/HospitalSystem.h"

#include <iostream>

int main()
{
    HospitalSystem hospitalSystem;
    char startupMessage[300];

    if (!hospitalSystem.initialize(startupMessage, 300))
    {
        std::cout << startupMessage << std::endl;
        return 1;
    }

    Gui gui;
    if (!gui.initialize(&hospitalSystem))
    {
        std::cout << "Could not load GUI font." << std::endl;
        return 1;
    }

    gui.run();
    return 0;
}
