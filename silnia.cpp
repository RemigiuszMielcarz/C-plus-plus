#include <cstdlib>
#include <iostream>
using namespace std;

//Silnia np. 4!=4*3*2*1
int silnia(int liczba)
{
    int wynik=1;
    for (int i = liczba; i > 1; i--)
    {
        wynik*=i;
    }
    return wynik;    
}

int main(void)
{
    cout << "Silnia wynosi" << silnia(6) << endl;
}