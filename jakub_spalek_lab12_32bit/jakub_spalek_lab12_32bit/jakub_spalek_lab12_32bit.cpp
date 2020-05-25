// Opracowane przez: Jakub Spa³ek, Aleksanda Pyrkosz, Daniel Wiêcek

#include <iostream>

using namespace std;

int GetLength(char* tab);
int FindSignPosition(char* tab, char sign);
void RighTrimSpaces(char* tab);
char* CopyStr(char* tab);

void Task1();
void Task2();
void Task3();
void Task4();

int main()
{
    Task1();
    Task2();
    Task3();
    Task4();
}

void Task1()
{
    cout << "---=== Zadanie 1 ===---" << endl;
    
    char* str = new char[15] {"Niskopoziomowe"};

    cout << "Ciag znakow: " << str << endl;
    cout << "Jego dlugosc: " << GetLength(str) << endl;

    system("pause");
    system("cls");

    delete[] str;
}

void Task2()
{
    cout << "---=== Zadanie 2 ===---" << endl;

    char* str = new char[15] {"Niskopoziomowe"};
    char sign = 'o';

    cout << "Ciag znakow: " << str << endl;
    cout << "Pierwsze wystapienie znaku '" << sign << "':" 
         << FindSignPosition(str, sign) << endl;

    system("pause");
    system("cls");
    
    delete[] str;
}

void Task3()
{
    cout << "---=== Zadanie 3 ===---" << endl;

    char* str = new char[18] {"Niskopoziomowe   "};

    cout << "Ciag znakow zawierajcy 3 prawe spacje: " << str << endl;
    cout << "Rozmiar przed obcieciem: " << GetLength(str) << endl;
    
    RighTrimSpaces(str);
    cout << "Rozmiar po obcieciu: " << GetLength(str) << endl;
    
    system("pause");
    system("cls");
    delete[] str;
}

void Task4()
{
    cout << "---=== Zadanie 4 ===---" << endl;

    char* str = new char[15] {"Niskopoziomowe"};
    char* copy = CopyStr(str);

    cout << "Ciag znakow: " << str << endl;
    cout << "Jego kopia: " << copy << endl;

    system("pause");
    system("cls");

    delete[] str, copy;
}

int GetLength(char* tab)
{
    __asm {
        push edi

        xor eax, eax        // eax = 0 (null)
        mov edi, tab        // adres tablicy znaków
        mov ecx, 1000       // liczba elementów
        cld                 // flaga kierunku danych
        repne scasb         // powtarzaj dopóki eax i [edi] nie s¹ równe
                            // (edi++, ecx--) tab[rozmiar] != null
        mov eax, 1000       
        sub eax, ecx        
        dec eax             // (1000 - ecx) - 1 = d³ugoœæ ³añcucha znaków
        
        pop edi
    }
}

int FindSignPosition(char* tab, char sign)
{
    __asm {
        push edi

        xor eax, eax         // eax = 0 (null) 
        mov al, [sign]       // znak, którego szukamy   
        mov edi, tab         // adres tablicy znaków
        mov ecx, 1000        // rozmiar tablicy
        cld                  // flaga kierunku danych
        repne scasb          // powtarzaj dopóki ecx > 0 lub ZF = 0, jeœli tab[n] == sign to ZF = 1
        mov eax, 1000
        sub eax, ecx
        dec eax              // (1000 - ecx) - 1 = pozycja znalezionego znaku

        pop edi
    }
}

void RighTrimSpaces(char* tab)
{
    int n = GetLength(tab);

    __asm {
        push edi
        push ebx

        mov edi, tab                // adres tablicy
        mov ecx, n                  // rozmiar
        mov al, ' '                 // szukany znak, czyli spacja

    WhileLoop:
        mov bl, [edi + ecx - 1]     // pobranie akutalnego znaku
        cmp bl, al                  // porównanie aktualnego znaku z szukanym
        jne Ender                   // je¿eli tab[i] = ' ' skacz do Ender
        dec ecx
        jnz WhileLoop               // dopóki n > 0 skacz do WhileLoop
    Ender:
        mov [edi + ecx], '\0'       // terminator przesuniêty na indeks,
                                    // w którym pojawia siê pierwsza spacja
        pop edi
        pop ebx
    }
}

char* CopyStr(char* tab)
{
    int n = GetLength(tab) + 1;
    char* copy = new char[n];

    __asm {
        push esi
        push edi

        xor eax, eax        // eax = 0 (null)
        mov esi, tab        // adres oryginalu
        mov edi, copy       // adres kopii
        mov ecx, n          // rozmiar tablicy
        cld                 // flaga kierunku danych
        repne movs          // powtarzaj dopóki ecx nierówne 0
                            // [esi++, edi++, ecx--]

        pop edi
        pop esi
    }

    return copy;
}
