#include "komputer.h"


void losowa_decyzja_komputera(int rozmiar, char ** pola) {
    int wiersz= rand() % rozmiar;
    int kolumna = rand() % rozmiar;
    if(pola[wiersz][kolumna] != 'X' && pola[wiersz][kolumna] != 'O') {
        pola[wiersz][kolumna] = 'X';
    }
    else {
        losowa_decyzja_komputera(rozmiar, pola);
    }
}


void sprawdz_wiersz(bool & ruch_wykonany, char sprawdz, int rozmiar, char ** pola) {
    for(int i = 0; i < rozmiar; i++) {
        int licz_symbole = 0;
        int numer_kolumny = -1;
        for(int j = 0; j < rozmiar; j++) {
            if(pola[i][j] == sprawdz) {
                licz_symbole++;
            }
            else if(pola[i][j] != 'X' && pola[i][j] != 'O') {
                numer_kolumny = j;
            }
        }
        if(licz_symbole == rozmiar - 1 && numer_kolumny >= 0) {
            pola[i][numer_kolumny] = 'X';
            ruch_wykonany = true;
            break;
        }
    }
}


void sprawdz_kolumne(bool & ruch_wykonany, char sprawdz, int rozmiar, char ** pola) {
    for(int j = 0; j < rozmiar; j++) {
        int licz_symbole = 0;
        int numer_wiersza = -1;
        for(int i = 0; i < rozmiar; i++) {
            if(pola[i][j] == sprawdz) {
                licz_symbole++;
            }
            else if(pola[i][j] != 'X' && pola[i][j] != 'O') {
                numer_wiersza = i;
            }
        }
        if(licz_symbole == rozmiar - 1 && numer_wiersza >= 0) {
            pola[numer_wiersza][j] = 'X';
            ruch_wykonany = true;
            break;
        }
    }
}


void sprawdz_przekatna_gora_dol(bool & ruch_wykonany, char sprawdz, int rozmiar, char ** pola) {
    int licz_symbole = 0;
    int pozycja = -1;

    for(int i = 0; i < rozmiar; ++i) {
        if(pola[i][i] == sprawdz) {
            licz_symbole++;
        }
        else if(pola[i][i] != 'X' && pola[i][i] != 'O') {
            pozycja = i;
        }
    }
    if(rozmiar - licz_symbole == 1 && pozycja >= 0) {
        pola[pozycja][pozycja] = 'X';
        ruch_wykonany = true;
    }
}


void sprawdz_przekatna_dol_gora(bool & ruch_wykonany, char sprawdz, int rozmiar, char ** pola) {
    int licz_symbole = 0;
    int wiersz= -1;
    int kolumna = -1;
    int tmp = 0;

    for(int i = rozmiar - 1; i >= 0; --i) {
        if(pola[i][tmp] == sprawdz) {
            licz_symbole++;
        }
        else if(pola[i][tmp] != 'X' && pola[i][tmp] != 'O') {
            wiersz= i;
            kolumna = tmp;
        }
        tmp++;
    }
    if(rozmiar - licz_symbole == 1 && wiersz>= 0) {
        pola[wiersz][kolumna] = 'X';
        ruch_wykonany = true;
    }
}


void decyzja_komputera(int rozmiar, char ** pola) {
    bool ruch_wykonany = false;

    //Komputer sprawdza czy może dać trójkę w wierszu
    sprawdz_kolumne(ruch_wykonany, 'X', rozmiar, pola);
    if(!ruch_wykonany) {
        sprawdz_wiersz(ruch_wykonany, 'X', rozmiar, pola);
    }
    if(!ruch_wykonany) {
        sprawdz_przekatna_gora_dol(ruch_wykonany, 'X', rozmiar, pola);
    }
    if(!ruch_wykonany) {
        sprawdz_przekatna_dol_gora(ruch_wykonany, 'X', rozmiar, pola);
    }

    //Komputer sprawdza czy gracz może być zblokowany
    if(!ruch_wykonany) {
        sprawdz_kolumne(ruch_wykonany, 'O', rozmiar, pola);
    }
    if(!ruch_wykonany) {
        sprawdz_wiersz(ruch_wykonany, 'O', rozmiar, pola);
    }
    if(!ruch_wykonany) {
        sprawdz_przekatna_gora_dol(ruch_wykonany, 'O', rozmiar, pola);
    }
    if(!ruch_wykonany) {
        sprawdz_przekatna_dol_gora(ruch_wykonany, 'O', rozmiar, pola);
    }

    //Komputer robi losowy ruch
    if(!ruch_wykonany) {
        losowa_decyzja_komputera(rozmiar, pola);
    }
}