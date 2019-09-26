# Hash generatorius
---
## v0.1
---
***Kompiliuoti naudojant šias komandas:***
1. Hashinimo funkcija: `g++ -o janhash main.cpp readData.cpp includes.cpp hash.cpp`
2. Collision testas su hash funkcija: `g++ -o coltest collisiontest.cpp readData.cpp includes.cpp hash.cpp`
3. Speed test su hash funkcija: `g++ -o speedtest speedtest.cpp readData.cpp includes.cpp hash.cpp`
4. Overlap testas (`overlap` branch'e): `g++ -o overlaptest overlaptest.cpp readData.cpp includes.cpp hash.cpp`

janhash maišos algoritmas, grįstas MD4 maišos algoritmo veikimo principais.

## janhash veikimo principas
---
1. Nuskaitomi duomenys į `string'ą`.
2. Prie duomenų `string'o`  pridedama tiek `'\0' char'ų`, kad duomenų ilgis būtų lygus 64 kartotiniui (ilgis dalintųsi iš 64 be liekanos).
3. Prie antro etapo metu gautų duomenų pridedama dar 64 simboliai, kurie sudaryti iš `'\0' char'ų` ir pradinių duomenų ilgio skaičiaus. (Jeigu pradiniai duomenys buvo 12 simbolių ilgio, 3 etapo metu pridedami šie simboliai: "...              12").
4. Sudaromi keturių žodžių buferiai:
```
	uint32_t buffer[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
```
4. Apibrėžiamos duomenų manipuliavimo funkcijos:
``` c++
uint32_t F(const uint32_t X, const uint32_t Y, const uint32_t Z)
{
	return (((X) & (Y)) | ((~X) & (Z)));
}

uint32_t G(const uint32_t X, const uint32_t Y, const uint32_t Z)
{
	return (((X) & (Y)) | ((X) & (Z)) | ((Y) & (Z)));
}

uint32_t H(const uint32_t X, const uint32_t Y, const uint32_t Z)
{
	return ((X) ^ (Y) ^ (Z));
}

void FF(uint32_t &a, const uint32_t b, const uint32_t c, const uint32_t d, const uint32_t k, int s)
{
	a = (a + F(b, c, d) + k);
	a = rotl32(a, s);
}

void GG(uint32_t &a, const uint32_t b, const uint32_t c, const uint32_t d, const uint32_t k, int s)
{
	a = (a + G(b, c, d) + k + 0x5a827999);
	a = rotl32(a, s);
}

void HH(uint32_t &a, const uint32_t b, const uint32_t c, const uint32_t d, const uint32_t k, int s)
{
	a = (a + H(b, c, d) + k + 0x6ed9eba1);
	a = rotl32(a, s);
}
```

5. Pakeisti pradiniai duomenys manipuliuojami 32 bitų blokais kartu su keturių žodžių buferiais funkcijomis FF, GG, HH (plačiau žiūrėti `hash.cpp/void hash()`).

6. 512 bitų duomenų manipuliuojami trimis raundais po 16 skirtingų kombinacijų. Antro raundo pavyzdys:
```
	Let [abcd k s] denote the operation
        a = (a + GG(b,c,d) + X[k] + 5A827999) <<< s.
        Do the following 16 operations.
    [ABCD  0  3][DABC  4  5][CDAB  8  9][BCDA 12 13]
    [ABCD  1  3][DABC  5  5][CDAB  9  9][BCDA 13 13]
    [ABCD  2  3][DABC  6  5][CDAB 10  9][BCDA 14 13]
    [ABCD  3  3][DABC  7  5][CDAB 11  9][BCDA 15 13]
```
7. Duomenų manipuliavimo pasekoje išmaišomi keturių žodžių buferiai, kuriuos sudėjus vieną šalia kito, gauname 128 bitų "hash'ą".

## Analizė
---
1. Testiniai įvedimo failų pavyzdžiai:
	1. Testas (Su skirtingi simboliai)
		* Failo `./duomenys/simb1.txt` hash'as: **e4e790a0965ef29885db2f3b0d4f3520**
		* Failo `./duomenys/simb2.txt` hash'as: **0b1c306d065006a70c1d4ddaeb47f6dd**
	2. Testas (Dideli failai, visiskai skiriasi)
		* Failo `./duomenys/100k1.txt` hash'as: 
		**07ced5a5858f6cc2d32b0bcda5e20014**
		* Failo `./duomenys/100k2.txt` hash'as: 
		**fcae5908641e557489f68cddda211f18**
	3. Testas (Dideli failai, skiriasi 1 simboliu)
		* Failo `./duomenys/100k_1simb_diff1.txt` hash'as:
		**68ba1eab9c696d3b8ab71ede169874c7**
		* Failo `./duomenys/100k_1simb_diff2.txt` hash'as:
		**5a3a079f0a1673576a7e9378822b2a9e**
	4. Testas (Tuščias failas)
		* Failo `./duomenys/empty.txt` hash'as:
		**66d662c950f0f6f1904063b1416f6f5f**
2. Kieviena eilutė teksto `konstitucija.txt` užhashinama tarp 0.0189-0.0319s.

3. Palyginus kiekvieną gautą hashą suhashinus `./duomenys/1mil.txt` failo eilutes, negauta nei viena sutampančių hashų pora.

4. Šiam analizės etapui sudarytas `./duomenys/1mil_2.txt` failas, kurio turinys aprašytas žemiau:
	* 830,584‬ eilučių po 5 simbolius.
	* Didžioji dalis gretimų eilučių skiriasi tik vienu simboliu.
    * 94 gretimos eilutės skirsis 3 simboliais.
    * ~8800 gretimų eilučių skirsis 2 simboliais.

	Testas buvo atliekamas tokiu principu:
	1. Apskaičiuojami pirmos ir antros eilučių hash'ai.
	2. Lyginama, kiek bitų skiriais gretimos eilutės.
	3. Pereinama prie antros ir trečios eilutės.
	4. Procesas kartojamas (vėl lyginamas kiek bitų skiriasi 2 ir 3 hash'ai ir t.t.).
	5. Skirtumai sumuojami.
	6. Suma padalinama iš patikrintų porų skaičiaus.
	7. Vidutinė pasikeitusių bitų dalis paverčiama į procentus.

	Testo rezultatai:
	```
	Vidutinis bitų skirtumas tarp gretimų hash'ų: 49.9989% 
	Max: 72.6525% (93 bitų skirtumas)
	Min: 28.125% (36 bitų skirtumas)
	```