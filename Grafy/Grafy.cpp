#include <iostream>
#include <fstream>
#include <cstdlib>

#include <ctime>
#include <string>

using namespace std;

struct lista_s  ///***|-> struktura reprezentujaca pojedyncza liste sasiedztwa dla jednego wierzcholka
{
    int v,w;    /// zmienna v przechowuje nam sasiadow, a w wage
    lista_s* nastepny;
};

void wypisz_dane(int wierzcholki, int il_krawedz, fstream& strumien) ///funkcja wypisujaca wygenerowane grafy do pliku
{
    int liczba_poz_wyk = il_krawedz - wierzcholki + 1;  ///liczba wykonan pozostalych po stworzeniu sciezki
                                                        ///laczacej wszystkie wierzcholki grafu
    int tmp = 0;
    int numer_wierzcholka = wierzcholki;
    int licznik = 0;

    strumien.open("dane.txt", ios_base::app);           ///otwieramy strumien danych zapisu do pliku

    strumien << wierzcholki<<" "<<il_krawedz<<" "<<rand()%wierzcholki<<endl;

                                                        ///wypisujemy ilosc wierzcholkow, krawedzi i wierzcholek startowy

                                                        ///wierzcholek startowy oraz wagi krawedzi sa pseudolosowe
    for(int i = 0; i < wierzcholki - 1 && i < il_krawedz -1 ; i++)

                                                        ///wypisujemy glowny cykl laczacy wszystkie wierzcholki po kolei
    {
        strumien << i<< " "<<i+1<<" "<<rand()%100+1<<endl;
    }
//laczy wierzcholki do gory o 1 (4->5 itd)

    while(licznik < liczba_poz_wyk) ///wypisujemy pozostale krawdzie w zaleznosci od wypelnienia
    {
        tmp = 0;

        while(licznik < liczba_poz_wyk && tmp < numer_wierzcholka - 2)
        {
            strumien << numer_wierzcholka - 1<<" "<< tmp <<" "<<rand()%10+1<<endl;

            licznik++;
            tmp++;
        }
        numer_wierzcholka--;
    }
    strumien.close();   

}
//laczy wierzcholki na dalsze odleglosci (1->20 itd)
void generuj_dane(fstream& strumien)
{
    int wierzcholki[5] = {10, 50, 100, 500, 1000};  ///****|-> tablica ilosci wierzcholkow zadanych w poleceniu projektu
    int max_krawedzi[5];                            ///****|-> tablica maksymalnych liczb krawedzi
    int krawedzie[5][4];                            ///****|-> tablica liczb krawedzi dla kazdego z przypadkow zadanych w projekcie
    int wypelnienie[4] = {25, 50, 75, 100};         ///****|-> tablica % wypelnien zadanych przypadkow

    strumien.open("dane.txt", ios_base::out);       ///****|-> otwieramy strumien do zapisu danych do pliku dane.txt
    strumien.close();                               ///****|-> zamykamy go, daje to pewnosc, ze plik uprzednio zostal
                                                    ///****|-> wyczyszczony z poprzednich danych

    for (int i = 0; i < 5; i++) ///******|-> generujemy kolejne przypadki dla ktorych pozniej rozpoczynamy                              //POCZ. 5
                                ///******|-> wypisywanie grafow do pliku poprzez funkcje wypisz_dane                                    //Test. 1
    {
        max_krawedzi [i] = wierzcholki[i] * (wierzcholki[i] - 1) /2;
        for (int z = 0; z < 4; z++)                                                                                                     //POCZ. 4
        {                                                                                                                               //test. 1
            krawedzie[i][z] = wypelnienie[z] * max_krawedzi[i] /100;    
            for(int c = 0; c < 100; c++) wypisz_dane (wierzcholki[i], krawedzie[i][z], strumien);                                       //POCZ. 100
        }                                                                                                                               //test. 1
    }

}

void wyswietl_sciezke(int* poprzednik, int* koszt_dojscia, int wierzch)
{
    int* wyswietlanie = new int [wierzch];  ///alokujemy pamiec dla tablicy dynamicznej do wyswietlania sciezki

    int n = 0;
    int m;

    for(int c = 0; c < wierzch; c++)    ///wyswietlamy dojscie do kazdego z wierzcholkow oraz koszt dojscia

                                        ///razem z wierzcholkiem startowym, dla niego koszt dojsca = 0
    {
        cout << c <<": ";
        for(m = c; m != -1 && n < wierzch; m = poprzednik[m])wyswietlanie [n++] = m;

        while(n)cout << wyswietlanie[--n] << " ";

        cout << "$" << koszt_dojscia[c] << endl;
    }
    delete [] wyswietlanie;             ///usuwamy tablice
}

void BF_lista(int wierzch, int kraw, int start, lista_s** tab_list)
{
    lista_s* sasiedzi;

    int max_int =2147483647;            ///maksymalna wartosc int w 32bit -> 64bit 9223372036854775807

    int* koszt_dojscia;                 ///inicjujemy wskaznik na tablice dynamiczna kosztow dojscia
    koszt_dojscia = new int [wierzch];  //laczny koszt dojscia startowego wierzcholka do jakiegoś wierzchołka

    int* poprzednik;                    ///inicjujemy wskaznik na tablice dynamiczna poprzednikow
    poprzednik = new int [wierzch];     //Droga jaką musimy przejść po punktach aby dojść z A do B

    for(int c = 0; c < wierzch; c++)
    {
        poprzednik[c] = -1;             ///przypisujemy wartosci tablicy poprzednikow -1 nie ma wierzcholka ujmenego
        koszt_dojscia[c] = max_int;     ///koszty dojscia ustawiamy na nieskonczonosc, tutaj na maksymalna wartosc inta
    }

    koszt_dojscia[start] = 0;           ///zerujemy koszt dojscia do naszego wierzcholka startowego

    for(int c = 1; c < wierzch; c++) //wykonujemy N-1 relaksacji
    {
        for(int b = 0; b < wierzch; b++)    ///przeszukujemy liste sasiedztwa w poszukiwaniu krawedzi dla
                                            ///danego wierzcholka relaksujac kolejne krawedzie
        {
            for(sasiedzi = tab_list[b]; sasiedzi; sasiedzi = sasiedzi -> nastepny)
            {
                if(koszt_dojscia[b] != max_int && koszt_dojscia[sasiedzi -> v] > koszt_dojscia[b] + sasiedzi -> w)
                {
                    koszt_dojscia[sasiedzi -> v] = koszt_dojscia [b] + sasiedzi -> w;
                    poprzednik[sasiedzi -> v] = b;
                }
            }
        }
    }
    /*
    cout <<"Lista sasiedztwa:\n";                                                                                   //ZAKOMENTUJ JEŻELI WIĘCEJ
    wyswietl_sciezke(poprzednik, koszt_dojscia, wierzch);*/
                            ///************* ^-> funkcja do wyswietlania drog oraz kosztow dojscia
}

void BF_macierz(int** graf_m, int wierzch, int kraw, int start)
{

    int max_int =2147483647;            ///maksymalna wartosc int w 32bit -> 64bit 9223372036854775807

    int* koszt_dojscia;                 ///inicjujemy wskaznik na tablice dynamiczna kosztow dojscia
    koszt_dojscia = new int [wierzch];

    int* poprzednik;                    ///inicjujemy wskaznik na tablice dynamiczna poprzednikow
    poprzednik = new int [wierzch];

    for(int c = 0; c < wierzch; c++)
    {
        poprzednik[c] = -1;             ///przypisujemy wartosci tablicy poprzednikow
        koszt_dojscia[c] = max_int;     ///koszty dojscia ustawiamy na nieskonczonosc, tutaj na maksymalna wartosc inta
    }

    koszt_dojscia[start] = 0;           ///zerujemy koszt dojscia do naszego wierzcholka startowego

    for(int c = 1; c < wierzch; c++)
    {
        for(int b = 0; b < wierzch; b++)
        {
            for(int v = 0; v < wierzch; v++)    ///przeszukujemy macierz sasiedztwa w poszukiwaniu krawedzi dla
                                                ///danego wierzcholka relaksujac kolejne krawedzie
            {
                if(koszt_dojscia[b] != max_int && graf_m[v][b] != 0 && koszt_dojscia[v] > koszt_dojscia[b] + graf_m[v][b])
                {
                    koszt_dojscia[v] = koszt_dojscia [b] +  graf_m[v][b];
                    poprzednik[v] = b;
                }
            }
        }
    }
    /*
    cout <<"Macierz sasiedztwa:\n";                                                                             //ZAKOMENTUJ JEŻELI WIĘCEJ
    wyswietl_sciezke(poprzednik, koszt_dojscia, wierzch);*/
                            ///************* ^-> funkcja do wyswietlania drog oraz kosztow dojscia
}

void wyswietl_lista(lista_s** tab_list, int wierzch)
{
    /// ################## |-> funkcja do wyswietlania tablicy list
    lista_s* lista_w;
    cout<< "lista:\n";
    for(int i = 0; i < wierzch; i++)
      {
        cout << "tab[" << i << "] =";
        lista_w = tab_list[i];
        while(lista_w)
        {
          cout << lista_w->v <<" ";
          lista_w = lista_w->nastepny;
        }
        cout << endl;
    }
    delete []lista_w; ///***|-> usuwamy liste sluzaca do wyswietlania tablicy list sasiedztwa
}

void graf_lista(int& wierzch, int& kraw, int& start, int** graf, lista_s** tab_list, lista_s* lista)
{
    int v1, v2, waga;

    for(int c = 0; c < wierzch; c++)   ///wypelniamy tablice list NULL'ami
    {
        tab_list[c] = NULL;

    }

    for(int c = 0; c < kraw; c++)   ///tworzymy listy dla grafu skierowanego
    {
        v1 = graf[c][0];    ///wczytujemy dane z reprezentacji grafu z pliku
        v2 = graf[c][1];
        waga = graf[c][2];

        lista = new lista_s;

        lista->v = v2;
        lista->w = waga;
        lista->nastepny = tab_list[v1];
        tab_list[v1] = lista;

    }

    for(int c = 0; c < kraw; c++)
    {
        v2 = graf[c][0];    ///wczytujemy dane z reprezentacji grafu z pliku
        v1 = graf[c][1];
        waga = graf[c][2];

        lista = new lista_s;

        lista->v = v2;
        lista->w = waga;
        lista->nastepny = tab_list[v1];
        tab_list[v1] = lista;
    }                           ///*** |-> funkcja odpowiada za tworzenie list dla grafu nieskierowanego

    /*wyswietl_lista(tab_list, wierzch);*/      ///**|-> funkcja odpowiedzialna za wyswietlanie listy sasiedztwa
}

void wyswietl_macierz(int** graf_m, int wierzch)
{
    ///********** |-> funkcja wyswietlajaca macierz sasiedztwa

    for(int c = 0; c < wierzch; c++)
    {
        for(int v = 0; v < wierzch; v++)
        {
            cout << graf_m[c][v] <<" ";
        }
        cout<<endl;
    }
}

void** graf_macierz(int& wierzch, int& kraw, int& start, int** graf, int** graf_m)
{
    int v1, v2, waga;
    int p = 0;

    for (int v = 0; v < wierzch; ++v)   ///zerujemy krawedzie; 0 = brak krawedzi
    {
        for(int b = p; b < wierzch; ++b)
        {
            graf_m[v][b] = 0;
            graf_m[b][v] = 0;
        }
        p++;
    }

    for (int v = 0; v < kraw; ++v)
    {
        v1 = graf[v][0];        ///wczytujemy dane z reprezentacji grafu z pliku
        v2 = graf[v][1];
        waga = graf[v][2];

        graf_m[v1][v2] = waga;  ///wpisujemy dane do macierzy sasiedztwa dla grafu nieskierowaniego
        graf_m[v2][v1] = waga;  ///dla skierowanego wylaczyc te linijke
    }
    /*wyswietl_macierz(graf_m, wierzch);*/
}

void** wczytaj_graf(int** graf, int& wierzch, int& kraw, int& start, ifstream& wejscie)
{
    /*cout<< wierzch <<" "<<kraw<<" "<<start<<endl;*/ ///wyswietlamy ilosc wierzcholkow, krawedzi i wierzcholek startowy
    for(int x = 0; x < kraw;x++)    ///wczytujemy graf z pliku do tablicy dynamicznej 2-wymiarowej
    {
        wejscie >> graf[x][0];
        wejscie >> graf[x][1];
        wejscie >> graf[x][2];

        /*cout<<graf[x][0]<<" ";
        cout<<graf[x][1]<<" ";
        cout<<graf[x][2]<<endl;*/ /// |-> wyswietlanie grafu, w celu wyswietlenia odkomentowac tu i na poczatku funkcji
    }
}

void znajdz_d_lista(int** graf, int& wierzch, int& kraw, int& start, fstream& wyjscie)
{
    double czas_trwania;
    clock_t czas1, czas2;           ///***|-> zmienne odpowiadajace za pomiar czasu

    lista_s** tab_list;
    lista_s* lista, *usuwanie;      ///***|-> struktury dynamiczne odpowiadajace za reprezentacje grafu
                                    ///***|-> w postaci listy sasiedztwa

    tab_list = new lista_s * [wierzch]; ///***|-> alokujemy pamiec dla tablicy list sasiedztwa

    graf_lista(wierzch, kraw, start, graf, tab_list, lista);    ///funkcja odpowiedzialna za tworzenie
                                                                ///tablicy dynamicznej list sasiedztwa

    czas1 = clock();                ///zaczynamy pomiar czasu trwania algorytmu

    BF_lista(wierzch, kraw, start, tab_list);   ///funkcja odpowiedzialna za szukanie najkrotszej sciezki algorytmem
                                                ///Bellmana-Forda dla listy sasiedztwa

    czas2 = clock() - czas1;        ///konczymy pomiar czasu trwania algorytmu


      for(int i = 0; i < wierzch; i++) ///usuwamy listy z tablicy list
      {
        lista = tab_list[i];
        while(lista)
        {
          usuwanie = lista;
          lista = lista->nastepny;
          delete usuwanie;
        }
      }
        delete [] tab_list;   ///usuwamy tablice list

    czas_trwania = (double) (czas2) / CLOCKS_PER_SEC;       ///konwertujemy czas trwania na zmienna double i obliczamy



    //wyjscie << "Czas trwania dla listy przy: "<<wierzch<<" i: "<<kraw*100/(wierzch * (wierzch - 1) /2)<<"% wypelnienia: "<<czas_trwania<<endl;


            ///*****|-> wypisujemy czas trwania algorytmu BF dla listy sasiedztwa strumieniem wyjscie
    wyjscie << "Czas trwania dla listy przy: "<<wierzch<<" i: "<<kraw*100/(wierzch * (wierzch - 1) /2)<<"% wypelnienia: "<<czas_trwania;
}

void znajdz_d_macierz(int** graf, int& wierzch, int& kraw, int& start, fstream& wyjscie)
{
    double czas_trwania;
    clock_t czas1, czas2;             ///***|-> zmienne odpowiadajace za pomiar czasu

    int** graf_m;                     ///***|-> tworzymy macierz sasiedztwa a nastepnie alokujemy dla niej pamiec

    graf_m = new int *[wierzch];
    for(int v = 0; v < wierzch; ++v)
    {
        graf_m[v] = new int [wierzch];
    }

    graf_macierz(wierzch, kraw, start, graf, graf_m);   ///funkcja odpowiedzialna za tworzenie macierzy sasiedztwa

    czas1 = clock();                          ///inicjujemy odmierzanie czasu

    BF_macierz(graf_m, wierzch, kraw, start); ///funkcja odpowiedzialna za szukanie najkrotszej sciezki algorytmem
                                              ///Bellmana-Forda dla macierzy sasiedztwa

    czas2 = clock() - czas1;        ///koniec odmierzania czasu trwania algorytmu

    for(int v = 0; v < wierzch; ++v) ///***|-> usuwamy macierz sasiedztwa
    {
        delete [] graf_m[v];
    }
    delete [] graf_m;

    czas_trwania = (double) (czas2) / CLOCKS_PER_SEC;       ///konwertujemy czas trwania na zmienna double i obliczamy

    //wyjscie << "Czas trwania dla macierzy przy: "<<wierzch<<" i: "<<kraw*100/(wierzch * (wierzch - 1) /2)<<"% wypelnienia: "<<czas_trwania<<endl;


    ///*****|-> wypisujemy czas trwania algorytmu BF dla listy sasiedztwa strumieniem wyjscie

    wyjscie << " dla macierzy: "<<czas_trwania<<endl;
}

void znajdz_droge(ifstream& wejscie)
{
    fstream wyjscie;
    int wierzch, kraw, start;
    int** graf;

    wyjscie.open("pomiar.txt", ios_base::app);  ///otwieramy strumien wyjsciowy do pliku pomiar.txt
                                                ///z prawem do zapisu w formie dopisywania danych
    for(int i = 0; i < 2000; i++)                                                                                       //POCZ.2000 //Test=1
    {


        wejscie >> wierzch;             ///wczytujemy kolejno: liczbe wierzcholkow, krawedzi i wierzcholek startowy
        wejscie >> kraw;
        wejscie >> start;

        graf = new int* [kraw];    ///alokowanie pamieci dla tablicy dynamicznej dwuwymiarowej

        for(int c = 0; c < kraw; c++)
        {
            graf[c] = new int [3];
        }

        wczytaj_graf(graf, wierzch, kraw, start, wejscie);          ///inicjujemy wczytywanie grafu z pliku
        znajdz_d_lista(graf, wierzch, kraw, start, wyjscie);        ///inicjujemy szukanie drogi dla listy sasiedztwa
        znajdz_d_macierz(graf, wierzch, kraw, start, wyjscie);      ///inicjujemy szukanie drogi dla macierzy sasiedztwa

        for(int z = 0; z < kraw; ++z) ///|-> usuwamy tablice dynamiczna przechowujaca dane grafu z pliku
        {
            delete [] graf[z];
        }
        delete [] graf;
    }
    wyjscie.close();    ///****|-> zamykamy strumien wyjsciowy
}

void pomiar(ifstream& strumien)
{

    strumien.open("dane.txt", ios_base::in); ///otwarcie strumienia do pliku z danymi wejsciowymi dla grafow
                                             ///z prawem do odczytu danych

    znajdz_droge(strumien);           ///**|-> uruchamiamy proces odnajdywania drogi dla grafow

    strumien.close();                        ///zamykamy strumien danych

}



int main()
{
    int wybor = 3;          ///zainicjowanie zmiennej odpowiedzialnej za menu wyboru

    fstream dane;
    ifstream wejscie;       ///zainicowanie zmiennych odpowiedzialnych za strumienie danych

    srand(time(NULL));      ///ustawienie pomiaru czasu od czasu zero
    
    do
    {
        ///*******************************|->menu wczytywania danych
        do
        {

            cout << "Wybierz opcje: 1. wygeneruj dane do pliku  2. pomiar \n";
            cin >> wybor;
            if(wybor > 2 || wybor < 1) cout << "Nie ma takiej opcji, wybierz ponownie\n";

        }while( wybor > 2 || wybor < 1 );

        switch( wybor )
        {
            case 1: generuj_dane(dane);///generuje dane i zapisuje je do pliku
            case 2: pomiar(wejscie);///wywoluje szereg funkcji odpowiedzialnych za wczytanie danych
                            ///oraz za odnalezienie najkrotszej drogi i zapisanie jej do pliku z wynikami
        }


    }while( wybor > 2 || wybor < 1 );
    
    /*
    generuj_dane(dane);///generuje dane i zapisuje je do pliku
    pomiar(wejscie);///wywoluje szereg funkcji odpowiedzialnych za wczytanie danych
                            ///oraz za odnalezienie najkrotszej drogi i zapisanie jej do pliku z wynikami
    */
    return 0;
}