#ifndef WYNIKGRY_H
#define WYNIKGRY_H

#include <iostream>
#include <cstdlib>

void kolumna_wygrana(bool & koniecgry, char symbol, int rozmiar, char ** pola);
void wiersz_wygrana(bool & koniecgry, char symbol, int rozmiar, char ** pola);
void przekatna_wygrana(bool & koniecgry, char symbol, int rozmiar, char ** pola);
void sprawdz_wygrana(bool & koniecgry, char symbol, int rozmiar, char ** pola);
void sprawdz_remis(bool & koniecgry, int rozmiar, char ** pola);

#endif