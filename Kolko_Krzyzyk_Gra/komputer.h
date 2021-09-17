#ifndef KOMPUTER_H
#define KOMPUTER_H

#include <iostream>
#include <cstdlib>

void sprawdz_wiersz(bool & ruch_wykonany, char sprawdz, int rozmiar, char ** pola);
void sprawdz_kolumne(bool & ruch_wykonany, char sprawdz, int rozmiar, char ** pola);
void sprawdz_przekatna_gora_dol(bool & ruch_wykonany, char sprawdz, int rozmiar, char ** pola);
void sprawdz_przekatna_dol_gora(bool & ruch_wykonany, char sprawdz, int rozmiar, char ** pola);
void losowa_decyzja_komputera(int rozmiar, char ** pola);
void decyzja_komputera(int rozmiar, char ** pola);

#endif