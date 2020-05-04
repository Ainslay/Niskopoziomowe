// Opracowane przez: Jakub Spa³ek, Aleksandra Pyrkosz, Daniel Wiêcek

#include <iostream>

using namespace std;

float Task1(float a, float b, float c, float d, float x);
void Task2(float a, float b, float p1, float p2, float xMin, float xMax, int size);

void PrintVector(float* vector, int size);

int main()
{
    cout << "Wynik dla zadania 1: " << Task1(2, 2, 4, 5, 3) << endl;
    cout << "Wynik dla zadania 2:\n";
    Task2(2,4,1,2,1,3,3);

    system("pause");
}

float Task1(float a, float b, float c, float d, float x)
{
    // ax^b - bx^c + cx + d
    // ONP: x b ^ a * x c ^ b * - c x * + d +

	float result = 0.0f;

	__asm {
        jmp jump
    fxtoy:
        fyl2x              // st(0) = y*log2x                  [y*log2x]
        fld st             // powiel st(0)                     [y*log2x : y*log2x]
        frndint            // zaokr¹glenie st(0)               [round(y*log2x) : y*log2x]
        fsub st(1), st     //                                  [round(y*log2x) : y*log2x-round(y*log2x)]
        fxch st(1)         // zamieñ st(0) i st(1) miejscami   [y*log2x-round(y*log2x) : round(y*log2x)]
        f2xm1              //                                  [2^(y*log2x-round(y*log2x))-1 : round(y*log2x)]
        fld1               //                                  [1 : 2^(y*log2x-round(y*log2x))-1 : round(y*log2x)]
        fadd               //                                  [2^(y*log2x-round(y*log2x)) : round(y*log2x)]
        fscale             //                                  [2^(y*log2x-round(y*log2x))*2^round(y*log2x) :
                            //                                  2^(y*log2x-round(y*log2x))+round(y*log2x)=2^round(y*log2x)
        fstp st(1)         // zdjêcie drugiego elementu ze stosu
        ret                // zwracamy st(0)
	
    jump:
        fld c               // [c]
        fld b               // [b : c]
        fld x               // [x : b : c]
        call fxtoy          // [x^b : c]
        fmul a              // [a*(x^b) : c]
        fxch st(1)          // [c : a*(x^b)]
        fld x               // [x : c : a*(x^b)]
        call fxtoy          // [x^c : a*(x^b)]
        fmul b              // [b*(x^c) : a*(x^b)
        fsubp st(1), st(0)  // [a*(x^b)-b(x^c)]
        fld c               // [c : a*(x^b)-b(x^c)]
        fmul x              // [c*x : a*(x^b)-b(x^c)]
        fadd d              // [c*x+d : a*(x^b)-b(x^c)]
        faddp st(1), st(0)  // [a*(x^b)-b(x^c)+ c*x+d]      

        fstp result         // zdjêcie ze stosu i zapis do wyniku
    }

	return result;
}

void Task2(float a, float b, float p1, float p2, float xMin, float xMax, int k)
{
    float* x = new float[k];
    float* y = new float[k];
    float buf = 180.0f;

    __asm {
        push esi
        push edi

        mov esi, x                  // adres pierwszej tablicy
        mov edi, y                  // adres drugiej tablicy
        mov ecx, k                  // iterator

        fld xMin                    // [xMin]
        fld xMax                    // [xMax : xMin]
        fsubrp st(1), st(0)         // [xMax-Xmin]
        fild k                      // [k : xMax-xMin]
        fdivp st(1), st(0)          // [krok]

        fld b                       // [b : krok]
        fld p1                      // [p1 : b : krok]
        fld p2                      // [p2 : p1 : b : krok]
        fld buf                     // [buf : p2 : p1 : b : krok]
        fld xMax                    // [xMax : buf : p2 : p1 : b : krok]

    loopko:
        fldpi                       // [PI : xMax : buf : p2 : p1 : b : krok]
        fmul st, st(3)              // [PI*p2 : xMax : buf : p2 : p1 : b : krok]
        fmul st, st(1)              // [PI*p2*xMax : xMax : buf : p2 : p1 : b : krok]
        fdiv st, st(2)              // [(PI*p2*xMax)/180 : xMax : buf : p2 : p1 : b : krok]
        fcos                        // [cos((PI*p2*xMax)/180) : xMax : buf : p2 : p1 : b : krok]
        fmul st, st(5)              // [b*cos((PI*p2*xMax)/180) : xMax : buf : p2 : p1 : b : krok]
        fstp [esi + 4 * ecx - 4]    

        fldpi                       // [PI : xMax : buf : p2 : p1 : b : krok]
        fmul st, st(3)              // [PI*p2 : xMax : buf : p2 : p1 : b : krok]
        fmul st, st(1)              // [PI*p2*xMax : xMax : buf : p2 : p1 : b : krok]
        fdiv st, st(2)              // [(PI*p2*xMax)/180 : xMax : buf : p2 : p1 : b : krok]
        fsin                        // [sin((PI*p2*xMax)/180) : xMax : buf : p2 : p1 : b : krok]
        fld st                      // [sin((PI*p2*xMax)/180) : sin((PI*p2*xMax)/180) : xMax : buf : p2 : p1 : b : krok]
        fmul                        // [sin((PI*p2*xMax)/180)^2 : xMax : buf : p2 : p1 : b : krok]
        fmul a                      // [a*sin((PI*p2*xMax)/180)^2 : xMax : buf : p2 : p1 : b : krok]
        fadd [esi + 4 * ecx - 4]    // [a*sin((PI*p2*xMax)/180)^2 + b*cos((PI*p2*xMax)/180) : xMax : buf : p2 : p1 : b : krok]

        fstp [edi + 4 * ecx - 4]    // [xMax : buf : p2 : p1 : b : krok]
        fst  [esi + 4 * ecx - 4]    // [xMax : buf : p2 : p1 : b : krok]
        fsub st, st(5)              // [xMax-krok : buf : p2 : p1 : b : krok]
    loop loopko                     // dopóki ecx > 0 skacz do loopko

        fstp st                     // [buf : p2 : p1 : b : krok]
        fstp st                     // [p2 : p1 : b : krok]
        fstp st                     // [p1 : b : krok]
        fstp st                     // [b : krok]
        fstp st                     // [krok]
        fstp st                     // []

        pop edi
        pop esi
    }

    cout << "X: ";
    PrintVector(x, k);
    cout << endl;

    cout << "Y: ";
    PrintVector(y, k);
    cout << endl;

    delete[] x, y;
}

void PrintVector(float* vector, int size)
{
    printf("[");
    for (int i = 0; i < size; i++)
    {
        printf("%f ", vector[i]);
    }
    printf("]");
}