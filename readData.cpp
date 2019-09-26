#include "readData.h"

#include <limits>
#include <streambuf>
#include <fstream>

string readFile(string fileName)
{
    std::ifstream input(fileName);
    string data;

    input.seekg(0, std::ios::end);
    data.reserve(input.tellg());
    input.seekg(0, std::ios::beg);

    data.assign((std::istreambuf_iterator<char>(input)),
                std::istreambuf_iterator<char>());

    input.close();

    return data;
}

string readInput()
{

    cout << "Iveskite duomenis: ";
    string data;

    getline(cin, data);

    return data;
}
