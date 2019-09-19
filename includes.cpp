#include "includes.h"

#include <limits>

int intInput(int low, int high)
{
	int a;
	bool power = true;
	while (power) {
		while (!(cin >> a))
		{
			cin.clear();	
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nIvesta bloga reiksme. Iveskite reiksme is naujo: ";
		}
		if (a <= high && a >= low) {
			power = false;
		}
		else {
			cout << "\nIvesta bloga reiksme. Iveskite reiksme is naujo: ";
		}
	}
	
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return a;
}
