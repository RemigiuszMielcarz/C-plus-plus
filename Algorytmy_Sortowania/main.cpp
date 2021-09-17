#include "Sortowania.h"
#include <iostream>
#include <fstream>
#include<ctime>
int main()
{


    fstream plik;
    plik.open("wyniki.txt", ios::app);
    int nr, N;
    double suma = 0;
    while (1)
    {
        suma = 0;
        std::cout << "1.kopcowanie\n";
        std::cout << "2.scalanie\n";
        std::cout << "3.shell\n";
        std::cout << "4.posortowany fragment kopcowanie\n";
        std::cout << "5.posortowany fragment scalanie\n";
        std::cout << "6.posortowany fragment shell\n";
        std::cout << "7.odwrotnie kopcowanie\n";
        std::cout << "8.odwrotnie scalanie\n";
        std::cout << "9.odwrotnie fragment shell\n";
        cin >> nr;
        
                std::cout << "podaj N\n";
                cin >> N;
            switch (nr)
            {
            case 1:
            {
              
                for (int i = 0; i < 100; i++)
                {
                    Sortowania nowy(N); //stworzony nowy obiekt klasy sortowania
                    nowy.Generuj();      //stworzenie wektora
                    
                    clock_t start = clock();
                    nowy.Sortuj_kopcowanie();
                    suma += clock() - start;
                }
                plik << suma / 100 << endl;
            }break;
            case 2:
            {
              
                for (int i = 0; i < 100; i++)
                {
                    Sortowania nowy(N);
                    nowy.Generuj();
                    clock_t start = clock();
                    nowy.Sortuj_przez_scalanie (0, N - 1);
                    suma += clock() - start;
                }
                plik << suma / 100 << endl;
            }break;
            case 3:
            {
                for (int i = 0; i < 100; i++)
                {
                    Sortowania nowy(N);
                    nowy.Generuj();
                    clock_t start = clock();
                    nowy.Sortuj_przez_shell();
                    suma += clock() - start;
                }
                plik << suma / 100 << endl;
            }
            break;
            case 4:
            {
                int procent;
                cout << "procent";
                cin >> procent;
          
                for (int i = 0; i < 100; i++)
                {
                    Sortowania nowy(N);
                    nowy.Generuj();


                    nowy.Sortuj_fragmentu_przez_kopcowanie(N * (procent / 100.0));
                    clock_t start = clock();
                    nowy.Sortuj_kopcowanie();
                    suma += clock() - start;
                }
                plik << suma / 100 << endl;
            }   break;
            case 5:
            {
                int procent;
                cout << "procent";
                cin >> procent;
        
                for (int i = 0; i < 100; i++)
                {
                    Sortowania nowy(N);
                    nowy.Generuj();
                    nowy.Sortuj_fragmentu_przez_scalanie(0, N * (procent / 100.0));
                    clock_t start = clock();
                    nowy.Sortuj_przez_scalanie(0, N - 1);
                    suma += clock() - start;
                }
                plik << suma / 100 << endl;
            }   break;
            case 6:
            {
                int procent;
                cout << "procent";
                cin >> procent;
             
                for (int i = 0; i < 100; i++)
                {
                    Sortowania nowy(N);
                    nowy.Generuj();
                    nowy.Sortuj_fragmentu_przez_shell(N * (procent / 100.0));
                    clock_t start = clock();
                    nowy.Sortuj_przez_shell();
                    suma += clock() - start;
                }
                plik << suma / 100 << endl;
            }
            break;
            case 7:
            {
            
                for (int i = 0; i < 100; i++)
                {
                    Sortowania nowy(N);
                    nowy.Generuj();


                    nowy.Sortuj_odwrotnie_przez_kopcowanie();
                    clock_t start = clock();
                    nowy.Sortuj_kopcowanie();
                    suma += clock() - start;
                }
                plik << suma / 100 << endl;
            }   break;
            case 8:
            {
            
               
                for (int i = 0; i < 100; i++)
                {
                    Sortowania nowy(N);
                    nowy.Generuj();
                    nowy.Sortuj_odwrotnie_przez_scalanie(0, N -1);
                    clock_t start = clock();
                    nowy.Sortuj_przez_scalanie(0, N - 1);
                    suma += clock() - start;
                }
                plik << suma / 100 << endl;
            }   break;
            case 9:
            {
              
            
                for (int i = 0; i < 100; i++)
                {
                    Sortowania nowy(N);
                    nowy.Generuj();
                    nowy.Sortuj_odwrotnie_przez_shell();
                    clock_t start = clock();
                    nowy.Sortuj_przez_shell();
                    suma += clock() - start;
                }
                plik << suma / 100 << endl;
            }
            break;
            }
        
        
    }
    return 0;
}

	
