#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

extern "C" void Procesor(INT64* vec1, INT64* vec2, INT64* result, INT64 n);
extern "C" double Koprocesor(double a, double b, double c, double x);

void PrintVector(INT64* vector, INT64 size);
INT64* CreateRandomVector(INT64 size);

void Task1();
void Task2();

int main()
{
    Task1();
    Task2();
}

void Task1()
{
    cout << "---=== ZADANIE 1 ===---\n";
    cout << "Roznica wektorow\n\n";

    INT64 n = 0;

    cout << "Podaj rozmiar wektora: ";
    cin >> n;

    srand(time(NULL));
    INT64* vec1 = CreateRandomVector(n);
    INT64* vec2 = CreateRandomVector(n);
    INT64* result = new INT64[n];

    Procesor(vec1, vec2, result, n);

    cout << "Wektor 1: ";
    PrintVector(vec1, n);

    cout << "Wektor 2: ";
    PrintVector(vec2, n);

    cout << "Wynik odejmowania: ";
    PrintVector(result, n);

    system("pause");
    system("cls");

    delete[] vec1, vec2, result;
}

void Task2()
{
    cout << "---=== ZADANIE 2 ===---\n";
    cout << "Wartosc wyrazenia\n\n";

    double a, b, c, x;

    cout << "Rownanie: 2x^2 - ax^2 * (b - c)\n\n";
    cout << "Podaj a: "; cin >> a;
    cout << "Podaj b: "; cin >> b;
    cout << "Podaj c: "; cin >> c;
    cout << "Podaj x: "; cin >> x;

    double result = Koprocesor(a, b, c, x);

    cout << "Wynik wyrazenia o podanych parametrach: " << result << endl;

    system("pause");
    system("cls");
}

INT64* CreateRandomVector(INT64 size)
{
    INT64* vector = new INT64[size];

    for (INT64 i = 0; i < size; i++)
    {
        vector[i] = rand() % (INT64)10 + (INT64)1;
    }

    return vector;
}

void PrintVector(INT64* vector, INT64 size)
{
    printf("[");
    for (INT64 i = 0; i < size; i++)
    {
        cout << vector[i] << " ";
    }
    printf("]\n");
}