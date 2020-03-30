// Opracowane przez: Jakub Spa³ek, Aleksandra Pyrkosz, Daniel Wiêcek

#include <iostream>
#include <windows.h>

extern "C" INT64  SumMatrix64(INT64** matrix, INT64 n1, INT64 n2);
extern "C" INT64* Multiply64(INT64** matrix, INT64* vector, INT64* result, INT64 rows, INT64 cols);

extern "C" INT64  SumMatrix32(int** matrix, int n1, int n2);
extern "C" INT64* Multiply32(int** matrix, int* vector, int* result, int rows, int cols);


void TestCode32();
void TestCode64();

int main()
{
    TestCode32();
    system("cls");
    TestCode64();
}

void TestCode32()
{
    std::cout << "WERSJA 32 BITOWA\n\n";

    int** matrix;
    int* vector;
    int* multiplicationResult;
    int rows, cols;

    std::cout << "Podaj liczbe wierszy: ";
    std::cin >> rows;
    std::cout << "Podaj liczbe  kolumn: ";
    std::cin >> cols;

    matrix = new int* [rows];
    vector = new int[cols];
    multiplicationResult = new int[cols];

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            printf("[%d][%d]: ", x, y);
            std::cin >> matrix[x][y];
        }
    }

    std::cout << "Suma elementow tej macierzy: " << SumMatrix32(matrix, rows, cols) << std::endl;

    std::cout << "Podaj wektor do mnozenia:\n";

    for (int i = 0; i < cols; i++)
    {
        printf("[%d]: ", i);
        std::cin >> vector[i];
    }

    std::cout << "Wynik mnozenia macierzy i wektora:\n";

    Multiply32(matrix, vector, multiplicationResult, rows, cols);

    for (int i = 0; i < rows; i++)
    {
        printf("[%d]: %d", i, multiplicationResult[i]);
        std::cout << std::endl;
    }

    system("pause");

    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix, vector, multiplicationResult;
}

void TestCode64()
{
    std::cout << "WERSJA 64 BITOWA\n\n";

    INT64** matrix;
    INT64* vector;
    INT64* multiplicationResult;
    INT64 rows, cols;

    std::cout << "Podaj liczbe wierszy: ";
    std::cin >> rows;
    std::cout << "Podaj liczbe  kolumn: ";
    std::cin >> cols;

    matrix = new INT64 * [rows];
    vector = new INT64[cols];
    multiplicationResult = new INT64[cols];

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new INT64[cols];
    }

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            printf("[%d][%d]: ", x, y);
            std::cin >> matrix[x][y];
        }
    }

    std::cout << "Suma elementow tej macierzy: " << SumMatrix64(matrix, rows, cols) << std::endl;

    std::cout << "Podaj wektor do mnozenia:\n";

    for (int i = 0; i < cols; i++)
    {
        printf("[%d]: ", i);
        std::cin >> vector[i];
    }

    std::cout << "Wynik mnozenia macierzy i wektora:\n";

    Multiply64(matrix, vector, multiplicationResult, rows, cols);

    for (int i = 0; i < rows; i++)
    {
        printf("[%d]: %I64u", i, multiplicationResult[i]);
        std::cout << std::endl;
    }

    system("pause");

    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix, vector, multiplicationResult;
}