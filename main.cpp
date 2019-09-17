#include "includes.h"
#include "hash.h"

int main()
{
     cout << "Pasirinkite:\n1. Skaityti duomenis is failo.\n2. Ivesti duomenis ranka.\n3. Iseiti." << endl;

     int choice = intInput();
     switch (choice)
     {
     case 1:
          cout << readFile() << endl;
          break;
     case 2:
          cout << readInput() << endl;
          break;
     default:
          cout << "Ivestas netinkamas pasirinkimas.";
     }

     return 0;
}