#include <iostream>
#include <time.h>

using namespace std;

void Task1Logarytm();
void Task3SumaElementowMacierzy();
void Task4PrzeslijSlowa();
void Task5Maks();
void Task6WartoscWyrazenia();
void Task7SwitchCase();
void Task8IleRazySieMiesci();
void Task9Case();

int main()
{
    //Task1Logarytm();
    //Task3SumaElementowMacierzy();
    //Task4PrzeslijSlowa();
    //Task5Maks();
    //Task6WartoscWyrazenia();
    //Task7SwitchCase();
    //Task8IleRazySieMiesci();
    Task9Case();
}

void Task1Logarytm()
{
    int a = 3;
    int x = 9;
    int* aptr = &a;
    int* xptr = &x;

    double wynik = 0.0f;

    // do koprocesora nie wrzucimy danych prosto z rejestrÛw procesora (eax, ecx itp)
    // np.
    // fld eax - !!!!!!!!!!!!! èLE !!!!!!!!!!!
    // mov eax, wskaznikDoPamieci
    // fld [eax] - DOBRZE, bo wrzucamy jakieú zapamiÍtane dane SPOD ADRESU zachowanego w rejestrze
    // NIE adres znajdujπcy siÍ w rejestrze

    __asm {
        mov eax, aptr
        mov edx, xptr

        fld1                        // [1]
        fild [edx]                  // [x : 1]
        fyl2x                       // [log2(x)]
        fld1                        // [1 : log2(x)]
        fild [eax]                  // [a : 1 : log2(x)]
        fyl2x                       // [log2(b) : log2(x)]
        fdiv                        // [logb(x)]
        fst wynik;
    }

    cout << "Zad1 Loga(x)\n";
    cout << "Wynik: " << wynik << endl;
    system("pause");
}

void Task3SumaElementowMacierzy()
{
    srand(time(NULL));

    float** macierz = new float* [3];

    for (int i = 0; i < 3; i++)
        macierz[i] = new float[3];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            macierz[i][j] = rand() % 5 + 1;
   
    double wynik = 0.0f;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << macierz[i][j] << " ";
        }
        cout << endl;
    }

    __asm {
        push edi
        push esi

        mov edi, macierz        // adres macierzy
        mov ecx, 3              // liczba wierszy, iterator pierwszej pÍtli
        fldz                    // wrzucenie na stos sumy [0]

        Pierwsza:
            mov esi, [edi + 4 * ecx - 4]        // konkretny wiersz
            mov eax, 3          // liczba kolumn

            Druga:
                fld [esi + 4 * eax - 4]         // macierz[i][j] - konkretny element [macierz[i][j] : suma]
                faddp st(1), st                 // dodanie do sumy [macierz[i][j] + suma]
                dec eax          
                jnz Druga           // dopÛki eax(j) > 0 skacz do Druga

        Loop Pierwsza           // dopÛki ecx(i) > 0 skacz do Pierwsza
        fst wynik              // zapisanie wyniku (zdjÍcie ze stosu)

        pop esi
        pop edi
    }
    
        
    cout << "Zad2 Suma elementow macierzy\n";
    cout << "Wynik: " << wynik << endl;
    system("pause");

    for (int i = 0; i < 3; i++)
        delete[] macierz[i];
    delete[] macierz;
}

void Task5Maks()
{
    int a = -3;
    int b = -1;
    int z = 0;

    __asm {
        mov eax, a
        mov edx, b
        mov z, eax

        cmp eax, edx
        jae pomin
        mov z, edx

        pomin:
    }

    cout << "Wieksza z liczb: " << z << endl;
    system("pause");
}

void Task6WartoscWyrazenia()
{
    double a = 2;
    double b = 3;
    double x = 4;

    double wynik = 0.0f;
    __asm {
        // a * sin(x) + b * cos(x)
        // ONP: x sin a * x cos b * +

        fld x                   // [x]
        fsin                    // [sin(x)]
        fmul a                  // [sin(x)*a]
        fld x                   // [x : sin(x)*a]
        fcos                    // [cos(x) : sin(x)*a]
        fmul b                  // [cos(x)*b : sin(x)*a]
        faddp st(1), st         // [sin(x)*a + cos(x)*b]
        fstp wynik
    }

    cout << "Wynik: " << wynik << endl;
    system("pause");
}

void Task7SwitchCase()
{
    float a = 6;
    float b = 5;
    float wynik = 0;

    __asm {
        fld a                   // [a]
        fld b                   // [b : a]
        fcomip st, st(1)        // [a]
        jb zero
        fmul a                  // [a*a]
        fmul a                  // [a*a*a]
        jmp koniec
        
        zero:
        fldz                    // [0 : a]
        fmulp st(1), st         // [0]
        
        koniec:
        fstp wynik
    }

    cout << "Wynik: " << wynik << endl;
    system("pause");
}

void Task8IleRazySieMiesci()
{
    int a = 7;
    int b = 3;
    int wynik = 0;

    __asm {
        mov eax, a
        mov edx, 0

        petla:
            sub eax, b
            cmp eax, 0
            jl pomin
            inc edx
            jmp petla

        pomin:
            mov wynik, edx
    }

    cout << "Wynik: " << wynik << endl;
    system("pause");
}

void Task9Case()
{
    int x = 2;
    int i = 4;
    int wynik = 0;

    __asm {
        mov eax, x
        mov edx, i

        cmp edx, 0
        je zero
        cmp edx, 1
        je jeden
        
        sub eax, 1
        jmp koniec

        zero:
            add eax, 2
            mul eax
            jmp koniec
        jeden:
            mov ecx, eax
            imul eax, ecx
            imul eax, ecx
        koniec:
            mov wynik, eax
    }

    cout << "Wynik: " << wynik << endl;
    system("pause");
}