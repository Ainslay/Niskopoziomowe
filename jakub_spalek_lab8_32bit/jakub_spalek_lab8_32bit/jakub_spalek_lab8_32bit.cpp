// Opracowane przez: Jakub Spa³ek, Aleksandra Pyrkosz, Daniel Wiêcek

#include <iostream>

using namespace std;

float Task1(float a, float b, float c, float d, float x);
float Task2(float a, float b, float c, float x);
float Task3SideSurfaceArea(float a, float b, float c);
float Task3Volume(float a, float b, float c);
double Task4(double* x, double* z, int N);

void GetVectorInput(double* vector, int size);
void PrintVector(double* vector, int size);

int main()
{
    cout << "Wynik dla zadania pierwszego: " << Task1(1, 1, 1, 1, 2) << endl;
    cout << "Wynik dla zadania drugiego: " << Task2(3, 1, 2, 2) << endl;
    cout << "Objetosc prostopadloscianu: " << Task3Volume(2, 2, 2) << endl;
    cout << "Pole powierzchni bocznej prostopadloscianu: " << Task3SideSurfaceArea(2, 2, 2) << endl;

    int N = 0;
    cout << "\nPodaj rozmiar (N) wektorów: "; cin >> N;
    
    double* x = new double[N];
    double* z = new double[N];

    cout << "Podaj wektor X:\n"; 
    GetVectorInput(x, N);
    
    cout << "Podaj wektor Z:\n"; 
    GetVectorInput(z, N);

    PrintVector(x, N);
    cout << " * ";
    PrintVector(z, N);
    cout << " = " << Task4(x, z, N) << endl;
    
    system("pause");
}

float Task1(float a, float b, float c, float d, float x)
{
    // y = ax^3 + bx^2 + cx + d
    // ONP: x x * x * a * d + x x * b * + c x * +

    float y = 0.0f;

    __asm {
        fld d               // przeniesienie d na stos                  [d]
        fld x               // przeniesienie x na stos                  [x : d]
        fld st              // powielenie x                             [x : x : d]
        // x x *
        fmul st, st(1)      // st(0) = st(0) * st(1) = x * x            [xx : x : d]

        fld st(1)           // przeniesienie na stos st(1) = x          [x : xx : x : d]
        // xx * x *
        fmul st, st(1)      // st(0) = x * xx                           [xxx : xx : x : d]
        // x x * x * a *
        fmul a              // st(0) = xxx * a                          [axxx : xx : x : d]

        // x x * x * a * d +
        faddp st(3), st     // st(3) = d + axxx, st(0) zdjête ze stosu  [xx : x : axxx+d]
        // x x * x * a * d + x x * b *
        fmul b              // st(0) = xx * b                           [xxb : x : axxx+d]
        // x x * x * a * d + x x * b * +
        faddp st(2), st     // st(2) = axxx+d + bxx, st(0) zdjête       [x : axxx+bxx+d]
        // c x *
        fmul c              // st(0) = x * c                            [cx : axxx+bxx+d]
        // x x * x * a * d + x x * b * + c x * +
        faddp st(1), st     // st(1) = axxx+bxx+d + xc, st(0) zdjête    [axxx+bxx+xc+d]
        
        fstp y              // zapis do wyniku, y = st(0), st(0) zdjête [stos pusty]
    }

    return y;
}

float Task2(float a, float b, float c, float x)
{
    // (a - 1)^3 * x + c * (b - a) + a(c - b)
    // ONP: a 1 - a 1 - * a 1 - * x * b a - c * + c b - * a +

    float y = 0.0f;

    __asm {
        fld a               // przeniesnie a na stos                [a]
        fld1                // przeniesnie 1 na stos                [1 : a]
        fsubp st(1), st     // st(1) = a - 1                        [a-1]
        fld st              // powielenie (a-1)                     [a-1 : a-1]
        fmul st(1), st      // st(1) = (a-1)*(a-1)                  [a-1 : (a-1)*(a-1)]
        fmulp st(1), st     // st(1) = (a-1)^3                      [(a-1)^3]
        fmul x              // st(0) = (a-1)^3 * x                  [(a-1)^3*x]

        fld b               // przeniesienie b na stos              [b : (a-1)^3*x]
        fld a               // przeniesienie a na stos              [a : b : (a-1)^3*x]
        fsubp st(1), st     // st(1) = b - a                        [b-a : (a-1)^3*x]
        fmul c              // st(0) = (b-a) * c                    [(b-a)*c : (a-1)^3*x]
        faddp st(1), st     // st(1) = (a-1)^3 + (b-a)*c            [(a-1)^3*x+(b-a)*c]

        fld c               // przeniesienie c na stos              [c : (a-1)^3*x+(b-a)*c]
        fld b               // przeniesienie b na stos              [b : c : (a-1)^3*x+(b-a)*c]
        fsubp st(1), st     // st(1) = c - b                        [c-b : (a-1)^3*x+(b-a)*c]
        fmul a              // st(0) = (c-b) * a                    [(c-b)*a : (a-1)^3*x+(b-a)*c]
        faddp st(1), st     // st(1) = (a-1)^3*x+(b-a)*c + (c-b)*a  [(a-1)^3*x+(b-a)*c+(c-b)*a]

        fstp y              // zapis do wyniku, y = st(0)           [stos pusty]
    }

    return y;
}

float Task3Volume(float a, float b, float c)
{
    // Objêtoœæ: abc
    // ONP: a b * c *

    float volume = 0.0f;

    __asm {
        fld c               // przeniesienie c na stos      [c]
        fld b               // przeniesienie b na stos      [b : c]
        fmul a              // st(0) = a * b                [a*b : c]
        fmulp st(1), st     // st(1) = a*b * c              [a*b*c]
        fstp volume         // zapis do wyniku, y = st(0)   [stos pusty]
    }

    return volume;
}

float Task3SideSurfaceArea(float a, float b, float c)
{
    // Pole powierzchni bocznej: 2ac + 2bc
    // ONP: 2 a * c * 2 b * c * +

    float area = 0.0f;

    __asm {
        fld c               // przeniesienie c na stos      [c]
        fld st              // powielenie c                 [c : c]
        fld1                // przeniesienie 1 na stos      [1 : c : c]
        fld st              // powielenie 1                 [1 : 1 : c : c]
        faddp st(1), st     // st(1) = 1 + 1                [2 : c : c]
        fld st              // powielenie 2                 [2 : 2 : c : c]
        fld a               // przeniesienie a na stos      [a : 2 : 2 : c : c]

        fmulp st(1), st     // st(1) = 2 * a                [2a : 2 : c : c]
        fmulp st(3), st     // st(3) = 2a * c               [2 : c : 2ac]
        fld b               // przeniesienie b na stos      [b : 2 : c : 2ac]
        fmulp st(1), st     // st(1) = 2 * b                [2b : c: 2ac]
        fmulp st(1), st     // st(1) = 2b * c               [2bc : 2ac]
        faddp st(1), st     // st(1) = 2ac + 2bc            [2ac+2bc]

        fstp area           // zapis do wyniku, y = st(0)   [stos pusty]
    }

    return area;
}

double Task4(double* x, double* z, int N)
{
    double result = 0.0f;

    __asm {
        push edi
        push esi

        mov ecx, N                            // iterator
        mov esi, x                            // adres pierwszego wektora
        mov edi, z                            // adres drugiego wektora
        fldz                                  // przeniesienie zera na stos   [s]
        
    Sum:
        fld  qword ptr [esi + 8 * ecx - 8]    // x[ecx-1]                     [x : s]
        fmul qword ptr [edi + 8 * ecx - 8]    // x[ecx-1] * z[ecx-1]          [x*z : s]
        faddp st(1), st                       // st(1) = s + x*z              [s]
    Loop Sum                                  // dopóki ecx > 0 skacz do Sum

        fstp result                           // zapis do wyniku, y = st(0)   [stos pusty]

        pop esi
        pop edi
    }

    return result;
}

void GetVectorInput(double* vector, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("[%i]: ", i);
        cin >> vector[i];
    }
}

void PrintVector(double* vector, int size)
{
    printf("[");
    for (int i = 0; i < size; i++)
    {
        printf("%f ", vector[i]);
    }
    printf("]");
}