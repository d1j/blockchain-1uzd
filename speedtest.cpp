#include <fstream>
#include <iostream>
#include <chrono>
#include <iostream>
#include <string>

#include "hash.h"

using namespace std;
using namespace std::chrono;

int main()
{
    ifstream input("./duomenys/konstitucija.txt");
    std::string str;
    double laikas = 0;

    while (std::getline(input, str))
    {
        auto start = high_resolution_clock::now();

        string a = janhash(str);

        auto end = high_resolution_clock::now();
        // auto duration = duration_cast<microseconds>(end - start);

        duration<double> diff = end - start;
        laikas += diff.count();
    }
    cout << laikas;
}
