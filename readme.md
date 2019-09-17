# Hash generatorius
---
## v0.1
---
Algoritmas
1. Prie žinutės pridedama (padding) tiek bitų, kad dalinant bitų skaičių iš 512 su moduliu, bitų skaičiaus liekana būtų 448. Nors vienas bitas visuomet bus pridėtas. Jeigu žinutė tenkina dalybos su liekana reikalavimą, pridedami nauji 512 bitų.
2. Paimamas žinutės ilgis, paverčiamas į 64 bitų duomenų formatą ir pridedamas prie su-"paddintų" duomenų. Nuo šios vietos, duomenų dydis bitais yra 512 kartotinis. (512bitai - 16 32bitų žodžių)
3. Sudaromi keturių žodžių buferiai:
```
word A: 01 23 45 67
word B: 89 ab cd ef
word C: fe dc ba 98
word D: 76 54 32 10
```