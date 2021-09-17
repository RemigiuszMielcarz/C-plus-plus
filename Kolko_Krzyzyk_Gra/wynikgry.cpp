#include "wynikgry.h"

void kolumna_wygrana(bool & koniecgry, char symbol, int rozmiar, char ** pola) {
    for(int i = 0; i < rozmiar; i++) {
        int liczsymbole = 0;
        for(int j = 0; j < rozmiar; j++) {
            if(pola[i][j] == symbol) {
                liczsymbole++;
            }
        }
        if(liczsymbole == rozmiar) {
            koniecgry = true;
        }
    }
}


void wiersz_wygrana(bool & koniecgry, char symbol, int rozmiar, char ** pola) {
    for(int i = 0; i < rozmiar; i++) {
        int liczsymbole = 0;
        for(int j = 0; j < rozmiar; j++) {
            if(pola[j][i] == symbol) {
                liczsymbole++;
            }
        }
        if(liczsymbole == rozmiar) {
            koniecgry = true;
        }
    }
}


void przekatna_wygrana(bool & koniecgry, char symbol, int rozmiar, char ** pola) {
    int liczsymbole = 0;
    for(int i = 0; i < rozmiar; ++i) {
        if(pola[i][i] == symbol) {
            liczsymbole++;
        }
    }
    if(liczsymbole == rozmiar) {
        koniecgry = true;
    }

    liczsymbole = 0;
    int tmp = 0;

    for(int i = rozmiar - 1; i >= 0; --i) {
        if(pola[i][tmp] == symbol) {
            liczsymbole++;
        }
        tmp++;
    }
    if(liczsymbole == rozmiar) {
        koniecgry = true;
    }
}


void sprawdz_wygrana(bool & koniecgry, char symbol, int rozmiar, char ** pola) {
    kolumna_wygrana(koniecgry, symbol, rozmiar, pola);
    wiersz_wygrana(koniecgry, symbol, rozmiar, pola);
    przekatna_wygrana(koniecgry, symbol, rozmiar, pola);
}


void sprawdz_remis(bool & koniecgry, int rozmiar, char ** pola) {
    bool remis = true;
    for(int i = 0; i < rozmiar; i++) {
        for(int j = 0; j < rozmiar; j++) {
            if(pola[i][j] != 'X' && pola[i][j] != 'O') {
                remis = false;
            }
        }
    }
    if(remis) {
        koniecgry = true;
    }
}