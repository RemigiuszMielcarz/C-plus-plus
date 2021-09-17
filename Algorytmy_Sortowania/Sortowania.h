
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;
class Sortowania
{
	vector<int> tablica;
    vector<int> tablica_tmp;

    int N;

public:
    Sortowania(int _N=0) { N = _N; }

    void Generuj()
    {
        for (int i = 0; i < N; i++)
        {
            tablica.push_back(rand());
        }
        tablica_tmp.resize(N);
    }
    
    void Sortuj_kopcowanie()
    {

        int i, j, m, k;
        int pom;
        for (i = 2; i <= N - 1; i++)
        {
            j = i;
            k = j / 2;
            pom = tablica[i];
            while ((k > 0) && (tablica[k] < pom))
            {
                tablica[j] = tablica[k];
                j = k;
                k = j / 2;
            }
            tablica[j] = pom;
        }
        for (i = N - 1; i > 1; i--)
        {
            swap(tablica[1], tablica[i]);
            j = 1;
            k = 2;
            while (k < i)
            {
                if ((k + 1 < i) && (tablica[k + 1] > tablica[k]))
                    m = k + 1;
                else
                    m = k;
                if (tablica[m] <= tablica[j]) break;
                swap(tablica[j], tablica[m]);
                j = m; k = j + j;
            }
        }
    }

    void Sortuj_fragmentu_przez_kopcowanie(int N)
    {
        int i, j, m, k;
        int pom;
        for (i = 2; i <= N - 1; i++)
        {
            j = i;
            k = j / 2;
            pom = tablica[i];
            while ((k > 0) && (tablica[k] < pom))
            {
                tablica[j] = tablica[k];
                j = k;
                k = j / 2;
            }
            tablica[j] = pom;
        }
        for (i = N - 1; i > 1; i--)
        {
            swap(tablica[1], tablica[i]);
            j = 1; k = 2;
            while (k < i)
            {
                if ((k + 1 < i) && (tablica[k + 1] > tablica[k]))
                    m = k + 1;
                else
                    m = k;
                if (tablica[m] <= tablica[j]) break;
                swap(tablica[j], tablica[m]);
                j = m; k = j + j;
            }
        }
    }


    void Sortuj_odwrotnie_przez_kopcowanie()
    {
        int i, j, m, k;
        int pom;
        for (i = 2; i <= N - 1; i++)
        {
            j = i;
            k = j / 2;
            pom = tablica[i];
            while ((k > 0) && (tablica[k] < pom))
            {
                tablica[j] = tablica[k];
                j = k;
                k = j / 2;
            }
            tablica[j] = pom;
        }
        for (i = N - 1; i > 1; i--)
        {
            swap(tablica[1], tablica[i]);
            j = 1; k = 2;
            while (k < i)
            {
                if ((k + 1 < i) && (tablica[k + 1] < tablica[k]))
                    m = k + 1;
                else
                    m = k;
                if (tablica[m] >= tablica[j]) break;
                swap(tablica[j], tablica[m]);
                j = m; k = j + j;
            }
        }
    }

    void Sortuj_fragmentu_przez_scalanie(int p, int k)
    {
        int s, i1, i2, i;

        s = (p + k + 1) / 2;
        if (s - p > 1) 
            Sortuj_fragmentu_przez_scalanie(p, s - 1);
        if (k - s > 0) 
            Sortuj_fragmentu_przez_scalanie(s, k);
        i1 = p; 
        i2 = s;
        for (i = p; i <= k; i++)
            if (((i1 == s) || ((i2 <= k) && (tablica[i1] > tablica[i2]))))
                tablica_tmp[i] = tablica[i2++];
            else
                tablica[i1++];
        for (i = p; i <= k; i++) 
            tablica[i] = tablica_tmp[i];
    }

    void Sortuj_przez_scalanie(int p, int k)
    {
        int s, i1, i2, i;

        s = (p + k + 1) / 2;
        if (s - p > 1)
            Sortuj_przez_scalanie(p, s - 1);
        if (k - s > 0)
            Sortuj_przez_scalanie(s, k);
        i1 = p; i2 = s;
        for (i = p; i <= k; i++)
            if (((i1 == s) || ((i2 <= k) && (tablica[i1] > tablica[i2]))))
                tablica_tmp[i] = tablica[i2++];
            else
                tablica[i1++];
        for (i = p; i <= k; i++) tablica[i] = tablica_tmp[i];
    }

    void Sortuj_odwrotnie_przez_scalanie(int p, int k)
    {
        int s, i1, i2, i;

        s = (p + k + 1) / 2;
        if (s - p > 1) 
            Sortuj_odwrotnie_przez_scalanie(p, s - 1);
        if (k - s > 0) 
            Sortuj_odwrotnie_przez_scalanie(s, k);
        i1 = p; 
        i2 = s;
        for (i = p; i <= k; i++)
            if (((i1 == s) || ((i2 <= k) && (tablica[i1] > tablica[i2]))))
                tablica_tmp[i] = tablica[i2++];
            else
                tablica[i1++];
        for (i = p; i <= k; i++) 
            tablica[i] = tablica_tmp[i];
    }


    void Sortuj_przez_shell()
    {
        int i, j, polowa, tmp;
        for (polowa = 1; polowa < N; polowa = 3 * polowa + 1);
        polowa /= 9;
        if (!polowa) polowa++;

        while (polowa)
        {
            for (j = N - polowa - 1; j >= 0; j--)
            {
                tmp = tablica[j];
                i = j + polowa;
                while ((i < N) && (tmp < tablica[i]))
                {
                    tablica[i - polowa] = tablica[i];
                    i += polowa;
                }
                tablica[i - polowa] = tmp;
            }
            polowa /= 3;
        }
    }

    void Sortuj_odwrotnie_przez_shell()
    {
        int i, j, polowa, tmp;
        for (polowa = 1; polowa < N; polowa = 3 * polowa + 1);
        polowa /= 9;
        if (!polowa) polowa++;

        while (polowa)
        {
            for (j = N - polowa - 1; j >= 0; j--)
            {
                tmp = tablica[j];
                i = j + polowa;
                while ((i < N) && (tmp < tablica[i]))
                {
                    tablica[i - polowa] = tablica[i];
                    i += polowa;
                }
                tablica[i - polowa] = tmp;
            }
            polowa /= 3;
        }
    }
    void Sortuj_fragmentu_przez_shell(int N)
    {
        int i, j, polowa, tmp;
        for (polowa = 1; polowa < N; polowa = 3 * polowa + 1);
        polowa /= 9;
        if (!polowa) polowa++;

        while (polowa)
        {
            for (j = N - polowa - 1; j >= 0; j--)
            {
                tmp = tablica[j];
                i = j + polowa;
                while ((i < N) && (tmp < tablica[i]))
                {
                    tablica[i - polowa] = tablica[i];
                    i += polowa;
                }
                tablica[i - polowa] = tmp;
            }
            polowa /= 3;
        }
    }

};

