// Opracowane przez: Jakub Spa³ek, Aleksandra Pyrkosz, Daniel Wiêcek

#include <iostream>
#include <Windows.h>

using namespace std;

extern "C" void SortVector(INT64* vector, INT64 n);
extern "C" void SortRealVector(float* vector, int n);

void Task1();
void Task2();
void PrintVector(INT64* vector, INT64 n);
void PrintVector(float* vector, int n);

int main()
{
    Task1();
    Task2();
}

void Task1()
{
    cout << "---=== Zadanie 1 ===---\n\n";
    INT64 n = 10;
    INT64* vec = new INT64[n]{ 2, 1, 10, 5, 4, 1, 3, 8, 11, 3 };

    cout << "Wektor przed sortowaniem: ";
    PrintVector(vec, n);

    SortVector(vec, n);

    cout << "Wektor po sortowaniu:     ";
    PrintVector(vec, n);

    cout << endl;
    system("pause");
    system("cls");
}

void Task2()
{
    cout << "---=== Zadanie 2 ===---\n\n";
    int n = 10;
    float* vec = new float[n]{ 2.5, 1.5, 5.1, 11.17, 4.7, 1.3, 3.2, 10.11, 3.1, 6.8 };

    cout << "Wektor przed sortowaniem: ";
    PrintVector(vec, n);

    SortRealVector(vec, n);

    cout << "Wektor po sortowaniu:     ";
    PrintVector(vec, n);

    cout << endl;
    system("pause");
    system("cls");
}

void PrintVector(INT64* vector, INT64 n)
{
    cout << "[";
    for (INT64 i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            cout << vector[i];
        }
        else
        {
            cout << vector[i] << ", ";
        }
    }
    cout << "]\n";
}

void PrintVector(float* vector, int n)
{
    cout << "[";
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            cout << vector[i];
        }
        else
        {
            cout << vector[i] << ", ";
        }
    }
    cout << "]\n";
}