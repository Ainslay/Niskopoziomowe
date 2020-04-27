// Opracowane przez: Jakub Spa³ek, Aleksandra Pyrkosz, Daniel Wiêcek

#include <iostream>

using namespace std;

extern "C" float Task1_64(float a, float b, float c, float d, float x);
extern "C" float Task2_64(float a, float b, float c, float x);
extern "C" float Task3SideSurfaceArea_64(float a, float b, float c);
extern "C" float Task3Volume_64(float a, float b, float c);
extern "C" double Task4_64(double* x, double* z, int N);

void GetVectorInput(double* vector, int size);
void PrintVector(double* vector, int size);

int main()
{
    cout << "Wynik dla zadania pierwszego: " << Task1_64(1, 1, 1, 1, 2) << endl;
    cout << "Wynik dla zadania drugiego: " << Task2_64(3, 1, 2, 2) << endl;
    cout << "Objetosc prostopadloscianu: " << Task3Volume_64(2, 2, 2) << endl;
    cout << "Pole powierzchni bocznej prostopadloscianu: " << Task3SideSurfaceArea_64(2, 2, 2) << endl;
    
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
    cout << " = " << Task4_64(x, z, N) << endl;

    system("pause");
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