//33 - 126
//1,060,321 eiluciu

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "hash.h"

using namespace std;

void genDuom()
{
    ofstream output("./duomenys/1mil.txt");
    for (int i = 33; i < 127; i++)
    {
        for (int j = 33; j < 127; j++)
        {
            for (int k = 33; k < 63; k++)
            {
                for (int z = 63; z < 65; z++)
                {
                    for (int x = 65; x < 67; x++)
                    {
                        char a;
                        string b = "";
                        a = (char)i;
                        b += a;
                        a = (char)j;
                        b += a;
                        a = (char)k;
                        b += a;
                        a = (char)z;
                        b += a;
                        a = (char)x;
                        b += a;
                        output << b << endl;
                    }
                }
            }
        }
    }
    output.close();
}

int main()
{
    vector<string> duom;
    duom.reserve(1070000);
    string a;

    ifstream input("./duomenys/1mil.txt");

    cout << "Reading data..." << endl;
    while (!input.eof())
    {
        input >> a;
        duom.push_back(a);
    }
    input.close();

    cout << "Data reformatting..." << endl;
    for (auto i = 0; i < duom.size(); i++)
    {
        duom[i] = janhash(duom[i]);
        if (i % 100000 == 0)
        {
            cout << ((double)i / (double)duom.size()) * 100 << "%" << endl;
        }
    }

    cout << "Data sorting..." << endl;
    sort(duom.begin(), duom.end());

    cout << "Collision detection..." << endl;

    //ofstream output("rez.txt");
    int collisions = 0;
    for (int i = 1; i < duom.size(); i++)
    {
        //output << duom[i] << endl;
        if (duom[i - 1] == duom[i])
        {
            collisions++;
        }
        if (i % 100000 == 0)
        {
            cout << ((double)i / (double)duom.size()) * 100 << "%" << endl;
        }
    }
    //output.close();

    cout << collisions << " collisions detected from " << duom.size() << " data entries";

    return 0;
}