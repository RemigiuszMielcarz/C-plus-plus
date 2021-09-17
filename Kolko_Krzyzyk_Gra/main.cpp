#include <time.h>
#include <string>
#include "wynikgry.h"
#include "komputer.h"      
#include <cstdlib>
#include <iostream>

void ustaw_rozmiar(int & wejscie) {
    std::cout << "Rozmiar planszy: ";
    std::cin >> wejscie;
    while (std::cin.fail() || wejscie < 3 || wejscie > 9 || wejscie % 2 == 0) {
        std::cin.clear();
        std::cin.ignore();
        system("cls");
        std::cout << "Zly rozmiar planszy." << std::endl << std::endl;
        std::cout << "Rozmiar planszy: ";
        std::cin >> wejscie;
    }
}


void rysuj_plansze(int rozmiar, char ** pola) {
    system("cls");

    std::cout << " ";
    for(int j = 0; j < rozmiar; ++j) {
        std::cout << "     " << j << "      ";
    }
    std::cout << std::endl;
    for(int i = 0; i < rozmiar; ++i) {
        for(int k = 0; k < 5; ++k) {
            for(int j = 0; j < rozmiar; ++j) {
                if(k == 2 && j == 0) {
                    std::cout << i;
                }
                else if(j == 0) {
                    std::cout << " ";
                }
                for(int s = 0; s < 11; ++s) {
                    if(s == 5 && k == 2) {
                        if(pola[i][j] == 'X' || pola[i][j] == 'O') {
                            std::cout << pola[i][j];
                        }
                        else {
                            std::cout << " ";
                        }
                    }
                    else {
                        std::cout << " ";
                    }
                }
                if(j < rozmiar - 1) {
                    std::cout << "#";
                }
            }
            std::cout << std::endl;
        }
        if(i < rozmiar - 1) {
            std::cout << " ";
            for(int j = 0; j < rozmiar; ++j) {
                std::cout << " # # # # #";
                if(j < rozmiar - 1) {
                    std::cout << " #";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void decyzja_gracza(int rozmiar, char ** pola) {
    int wiersz;
    int kolumna;

    std::cout << "Wybierz wiersz: ";
    std::cin >> wiersz;
    std::cout << "Wybierz kolumne: ";
    std::cin >> kolumna;
    
    while (std::cin.fail()) {
        rysuj_plansze(rozmiar, pola);
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Nieprawidlowy ruch." << std::endl << std::endl;
        std::cout << "Wybierz wiersz: ";
        std::cin >> wiersz;
        std::cout << "Wybierz kolumne: ";
        std::cin >> kolumna;
    }

    if(wiersz >= rozmiar || wiersz < 0 || kolumna >= rozmiar || kolumna < 0 ) {
        rysuj_plansze(rozmiar, pola);
        std::cout << "Nieprawidlowy numer kolumny lub wiersza." << std::endl << std::endl;
        decyzja_gracza(rozmiar, pola);
    }
    else {
        if(pola[wiersz][kolumna] != 'X' && pola[wiersz][kolumna] != 'O') {
            pola[wiersz][kolumna] = 'O';
            rysuj_plansze(rozmiar, pola);
        }
        else {
            rysuj_plansze(rozmiar, pola);
            std::cout << "To pole jest juz zajete." << std::endl << std::endl;
            decyzja_gracza(rozmiar, pola);
        }
    }
}


int main() {
    int rozmiar;
    ustaw_rozmiar(rozmiar);

    char ** plansza;
    plansza = new char *[rozmiar];

    for(int i = 0; i < rozmiar; ++i) {
        plansza[i] = new char [rozmiar];
        for(int j = 0; j < rozmiar; ++j) {
            plansza[i][j] = '0';
        }
    }
    
    std::string koncowy_napis;
    bool koniec_gry = false;
    srand(time(0));

    rysuj_plansze(rozmiar, plansza);

    while(!koniec_gry) {
        sprawdz_remis(koniec_gry, rozmiar, plansza);
        if(koniec_gry) {
            koncowy_napis = "Remis! ";
            break;
        }

        decyzja_gracza(rozmiar, plansza);
        sprawdz_wygrana(koniec_gry, 'O', rozmiar, plansza);
        if(koniec_gry) {
            koncowy_napis = "Wygrales! ";
            break;
        }

        sprawdz_remis(koniec_gry, rozmiar, plansza);
        if(koniec_gry) {
            koncowy_napis = "Remis! ";
            break;
        }

        decyzja_komputera(rozmiar, plansza);
        rysuj_plansze(rozmiar, plansza);
        sprawdz_wygrana(koniec_gry, 'X', rozmiar, plansza);
        if(koniec_gry) {
            koncowy_napis = "Przegrales. ";
            break;
        }
    }

    std::cout << koncowy_napis << "Nacisnij enter aby wyjsc z konsoli." << std::endl;
    std::cin.get();
    std::cin.get();

    return 0;
}