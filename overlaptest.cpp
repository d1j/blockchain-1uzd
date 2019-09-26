#include <iostream>
#include <fstream>
#include <string>

#include "hash.h"

using namespace std;

// compute number of different bits
int compare_32bits(uint32_t A, uint32_t B)
{
    int count = 0;

    // since, the numbers are less than 2^31
    // run the loop from '0' to '31' only
    for (int i = 0; i < 32; i++)
    {
        // right shift both the numbers by 'i' and
        // check if the bit at the 0th position is different
        if (((A >> i) & 1) != ((B >> i) & 1))
        {
            count++;
        }
    }
    return count;
}

//Returns the number of bits that differs between the submitted hashes
int compare_janhash(uint32_t a[], uint32_t b[])
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        count += compare_32bits(a[i], b[i]);
    }
    return count;
}

using namespace std;

int main()
{
    ifstream input("./duomenys/1mil_2.txt");
    string str;
    getline(input, str);
    uint32_t *prev = janhash(str), *curr;
    int num_iter = 0;
    int sum = 0;
    int min = 129, max = -1;
    while (getline(input, str))
    {
        curr = janhash(str);
        int comp = compare_janhash(prev, curr);
        if (comp < min)
        {
            min = comp;
        }
        if (comp > max)
        {
            max = comp;
        }
        sum += comp;
        num_iter++;
        prev = curr;
    }

    double avg = (double)sum / (double)num_iter;

    cout << "Vidurkis: " << avg / 128 * 100 << endl;
    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;

    input.close();

    return 0;
}