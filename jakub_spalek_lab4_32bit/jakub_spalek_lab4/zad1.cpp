#include <iostream>

int SumujElementyTablicy32(int* tab, int n);
int SumujElementyTablicy32jnz(int* tab, int n);
void ZerujTablice(int* tab, int n);
void WypiszTablice(int* tab, int n);
int Max(int* tab, int n);
int Min(int* tab, int n);
int IloczynSkalarny(int* tab1, int* tab2, int n);

using namespace std;

int main()
{
    int n;
    int* tablica;

    cout << "Podaj liczbe elementow tablicy 32b: ";
    cin >> n;

    tablica = new int[n];

    cout << "Podaj wartosci elementow (32b):\n";
    for (int i = 0; i < n; i++)
    {
        printf("[%d]: ", i);
        std::cin >> tablica[i];
    }


    cout << "Suma tych elementow wynosi (loop): " << SumujElementyTablicy32(tablica, n)    << endl;
    cout << "Suma tych elementow wynosi (jnz): "  << SumujElementyTablicy32jnz(tablica, n) << endl;
    cout << "Najwiekszy element tablicy: " << Max(tablica, n) << endl;
    cout << "Najmniejszy element tablicy: " << Min(tablica, n) << endl;
    cout << endl;

    int* tablica2;
    tablica2 = new int[n];

    cout << "Podaj wartosci elementow drugiej tablicy(32b):\n";
    for (int i = 0; i < n; i++)
    {
        printf("[%d]: ", i);
        std::cin >> tablica2[i];
    }

    cout << "Iloczyn skalarany tych dwoch tablic wynosi: " << IloczynSkalarny(tablica, tablica2, n) << endl;

    ZerujTablice(tablica, n);
    cout << "Tablica po wyzerowaniu: ";
    WypiszTablice(tablica, n);

    cout << endl;
    system("pause");

    delete[] tablica;
    delete[] tablica2;
}

int SumujElementyTablicy32(int* tab, int n)
{
    int sum = 0;

    __asm {
        push ebx

        xor eax, eax                     // zerowanie wyniku sumowania
        mov ebx, tab                     // pobranie adresu tablicy
        mov ecx, n                       // przygotowanie iteratora
        
        Suma:
            add eax, [ebx + 4 * ecx - 4] //eax += el_tablicy
            loop Suma                    // dopoki ecx > 0 skocz do Suma
        
        mov sum, eax                 // zapisanie wyniku

        pop ebx
    }

    return sum;
}

int SumujElementyTablicy32jnz(int* tab, int n)
{
    int sum = 0;

    __asm {
        push eax                         // przygotowanie rejestrow do pracy
        push ebx
        push ecx

        xor eax, eax                     // zerowanie wyniku sumowania
        mov ecx, n                       // przygotowanie iteratora
        mov ebx, tab                     // pobranie adresu tablicy
        
        Suma :
        add eax, [ebx + 4 * ecx - 4]     //eax += el_tablicy
            dec ecx
            jnz Suma                     // dopoki ecx > 0 skocz do Suma

            mov sum, eax                 // zapisanie wyniku

        pop ecx                          // przywrocenie stanu rejestrow
        pop ebx
        pop eax
    }

    return sum;
}

void ZerujTablice(int* tab, int n)
{
    __asm {
        push ebx
        push ecx

        mov ecx, n                       // przygotowanie iteratora
        mov ebx, tab                     // pobranie adresu tablicy

        Zeruj:
            mov  [ebx + 4 * ecx - 4], 0   // tab[i] = 0
            loop Zeruj                    // dopoki ecx > 0 skocz do Zeruj
        
        pop ecx                          
        pop ebx
    }
}

void WypiszTablice(int* tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << tab[i] << " ";
    }
}

int IloczynSkalarny(int* tab1, int* tab2, int n)
{
    int sum = 0;

    __asm {
        push ebx
        push esi

        mov ecx, n              // iterator
        mov ebx, tab1           // adres pierwszej tablicy
        mov edx, tab2           // adres drugiej tablicy
        xor eax, eax            // suma = 0

        Suma:
            mov  esi, [ebx + 4 * ecx - 4]
            imul esi, [edx + 4 * ecx - 4]       // tab1[i] * tab2[i]
            add  eax, esi                       // dodaj wynik do sumy
            loop Suma                           // dopoki i > 0 skacz do Suma

        mov sum, eax                            // zapisz wynik w zmiennej sum

        pop esi
        pop ebx
    }

    return sum;
}

int Max(int* tab, int n)
{
    int max = 0;

    __asm {
        push ebx

        mov ebx, tab                    // adres tablicy
        mov ecx, n                      // iterator (iterujemy od konca)
        mov eax, [ebx + 4 * ecx - 4]    // ustawiamy jako max ostatni element
        dec ecx                         // pomniejsz o 1 (ze wzgledu na to ze n-ty element jest teraz min)

        Szukaj:
            cmp eax, [ebx + 4 * ecx - 4]    // jesli eax jest mniejsze od tab[i] 
            cmovl eax, [ebx + 4 * ecx - 4]  // przenies tab[i] do eax
            loop Szukaj                     // dopoki i > 0 skacz do Szukaj
        
        mov max, eax                    // zapisz wynik do zmiennej max
     
        pop ebx
    }

    return max;
}

int Min(int* tab, int n)
{
    int min = 0;

    __asm {
        push ebx

        mov ebx, tab                    // adres tablicy
        mov ecx, n                      // iterator (iterujemy od konca)
        mov eax, [ebx + 4 * ecx - 4]    // ustawiamy jako max ostatni element
        dec ecx                         // pomniejsz o 1 (ze wzgledu na to ze n-ty element jest teraz min)

        Szukaj :
            cmp eax, [ebx + 4 * ecx - 4]    // jesli eax jest mniejsze od tab[i] 
            cmovg eax, [ebx + 4 * ecx - 4]  // przenies tab[i] do eax
            loop Szukaj                     // dopoki i > 0 skacz do Szukaj

        mov min, eax                    // zapisz wynik do zmiennej min
        
        pop ebx
    }

    return min;
}
