#include "includes.h"

#include <limits>

int intInput()
{
    int a;
    while (!(cin >> a))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\nIvesta bloga reiksme. Iveskite reiksme is naujo: ";
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return a;
}