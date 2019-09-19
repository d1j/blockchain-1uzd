#include "includes.h"
#include "hash.h"
#include "readData.h"

#include <fstream>

int main()
{
     bool power = true;
     while (power)
     {
          cout << "Pasirinkite:\n1. Skaityti duomenis is failo.\n2. Ivesti duomenis ranka.\n3. Iseiti." << endl;

          int choice = intInput(1, 3);
          string data;
          switch (choice)
          {
          case 1:
               data = readFile();
               break;
          case 2:
               data = readInput();
               break;
          case 3:
               power = false;
               break;
          default:
               cout << "Ivestas netinkamas pasirinkimas.";
          }

          string result = hash(data);
          cout << result << endl
               << endl;
     }

     return 0;
}

/*
1 -		74bed151bef3045be39aca84d1a33895
2 -		8df75c1d25aa1a0b66e0a173f3479042
3 -		3e41f456dc820c3f8cdba943805e82df
4 -		45fca61e6853b2cafb7636f1f26c212a
5 -		02045971a20d7da9d8bd2646a372fd74
6 -		f89f363f0775be915573205ab951b519
7 -		ca63ed803c97a77fcac5924843dc2d35
8 -		1405f3c090b5943b5af488e10823288f
9 -		ab57d4520739639523df64e6d47c1585
10 -	ca668cc966a6fe84862d23bcb4065007
*/