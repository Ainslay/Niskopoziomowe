#include <iostream>

extern "C" _int64 SumujElementyTablicy64(_int64 n, _int64 * tab);
extern "C" _int64 SumujElementyTablicy64jnz(_int64 n, _int64 * tab);
extern "C" _int64 Max64(_int64 n, _int64 * tab);
extern "C" _int64 Min64(_int64 n, _int64 * tab);
extern "C" _int64 ZerujTablice64(_int64 n, _int64 * tab);
extern "C" _int64 IloczynSkalarny64(_int64 * tab1, _int64 * tab2, _int64 n);

using namespace std;

void WypiszTablice(_int64 n, _int64* tab);

int main()
{
    _int64 n;
    _int64* tablica;

    cout << "Podaj liczbe elementow tablicy 64b: ";
    cin >> n;

    tablica = new _int64[n];

    cout << "Podaj wartosci elementow (64b):\n";
    for (_int64 i = 0; i < n; i++)
    {
        printf("[%I64u]: ", i);
        std::cin >> tablica[i];
    }

    cout << "Suma tych elementow wynosi (loop): " << SumujElementyTablicy64(n, tablica) << endl;
    cout << "Suma tych elementow wynosi (jnz): " << SumujElementyTablicy64jnz(n, tablica) << endl;
    cout << "Najwiekszy element tablicy: " << Max64(n, tablica) << endl;
    cout << "Najmniejszy element tablicy: " << Min64(n, tablica) << endl;

    _int64* tablica2 = new _int64[n];

    cout << "Podaj wartosci elementow drugiej tablicy (64b):\n";
    for (_int64 i = 0; i < n; i++)
    {
        printf("[%I64u]: ", i);
        std::cin >> tablica2[i];
    }
    cout << "Iloczyn skalarany tych dwoch tablic wynosi: " << IloczynSkalarny64(tablica, tablica2, n) << endl;

    ZerujTablice64(n, tablica);
    cout << "Tablica po wyzerowaniu: ";
    WypiszTablice(n, tablica);

    system("pause");
}

void WypiszTablice(_int64 n, _int64* tab)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << tab[i] << " ";
    }
}