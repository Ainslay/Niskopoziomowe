#include <iostream>
#include <Windows.h>

extern "C" void SumMatrices64(INT64** matrixA, INT64** matrixB, INT64** result, INT64 rows, INT64 cols);
extern "C" void MultiplyMatrices64(INT64** matrixA, INT64** matrixB, INT64** result, INT64 rowsA, INT64 colsA, INT64 colsB);
extern "C" INT64  MinMatrix3D64(INT64*** matrix, INT64 rows, INT64 cols, INT64 depth);

void PrintMatrix2D(INT64** matrix, INT64 rows, INT64 cols);
void PrintMatrix3D(INT64*** matrix, INT64 rows, INT64 cols, INT64 depth);

int main()
{
    INT64** matrixA;
    INT64** matrixB;
    INT64** sumResult;
    INT64 rowsA, colsA;
    INT64 rowsB, colsB;

    std::cout << "---=== SUMOWANIE ===---\n";
    std::cout << "Podaj liczbe wierszy: ";
    std::cin >> rowsA;
    std::cout << "Podaj liczbe  kolumn: ";
    std::cin >> colsA;

    matrixA = new INT64* [rowsA];
    matrixB = new INT64* [rowsA];
    sumResult = new INT64* [rowsA];

    for (INT64 i = 0; i < rowsA; i++)
    {
        matrixA[i] = new INT64[colsA];
        matrixB[i] = new INT64[colsA];
        sumResult[i] = new INT64[colsA];
    }

    std::cout << "Wprowadz macierz A:\n";
    for (INT64 x = 0; x < rowsA; x++)
    {
        for (INT64 y = 0; y < colsA; y++)
        {
            printf("[%I64u][%I64u]: ", x, y);
            std::cin >> matrixA[x][y];
        }
    }

    std::cout << "Wprowadz macierz B:\n";
    for (INT64 x = 0; x < rowsA; x++)
    {
        for (INT64 y = 0; y < colsA; y++)
        {
            printf("[%I64u][%I64u]: ", x, y);
            std::cin >> matrixB[x][y];
        }
    }

    SumMatrices64(matrixA, matrixB, sumResult, rowsA, colsA);
    std::cout << "Wynik sumowania tych macierzy:\n";
    PrintMatrix2D(sumResult, rowsA, colsA);

    for (INT64 i = 0; i < rowsA; i++)
    {
        delete[] matrixA[i], matrixB[i], sumResult[i];
    }

    delete[] matrixA, matrixB, sumResult;

    //+++++++++++++++++++++++++++++++++++++++++++++++

    std::cout << "---=== MNOZENIE ===---\n";
    std::cout << "Podaj liczbe wierszy macierzy A: ";
    std::cin >> rowsA;
    std::cout << "Podaj liczbe  kolumn macierzy A: ";
    std::cin >> colsA;

    matrixA = new INT64* [rowsA];

    for (INT64 i = 0; i < rowsA; i++)
    {
        matrixA[i] = new INT64[colsA];
    }

    std::cout << "Wprowadz macierz A:\n";
    for (INT64 x = 0; x < rowsA; x++)
    {
        for (INT64 y = 0; y < colsA; y++)
        {
            printf("[%I64u][%I64u]: ", x, y);
            std::cin >> matrixA[x][y];
        }
    }

    std::cout << "Podaj liczbe wierszy macierzy B: ";
    std::cin >> rowsB;
    std::cout << "Podaj liczbe  kolumn macierzy B: ";
    std::cin >> colsB;

    INT64** mulResult = new INT64* [rowsA];

    for (INT64 i = 0; i < rowsA; i++)
    {
        mulResult[i] = new INT64[colsB];
    }

    if (colsA == rowsB)
    {
        matrixB = new INT64* [rowsB];

        for (INT64 i = 0; i < rowsB; i++)
        {
            matrixB[i] = new INT64[colsB];
        }

        std::cout << "Wprowadz macierz B:\n";
        for (INT64 x = 0; x < rowsB; x++)
        {
            for (INT64 y = 0; y < colsB; y++)
            {
                printf("[%I64u][%I64u]: ", x, y);
                std::cin >> matrixB[x][y];
            }
        }

        MultiplyMatrices64(matrixA, matrixB, mulResult, rowsA, colsA, colsB);

        std::cout << "Wynik mnozenia tych dwoch macierzy:\n";
        PrintMatrix2D(mulResult, rowsA, colsB);

        for (INT64 i = 0; i < rowsB; i++)
        {
            delete[] matrixB[i];
        }
    }
    else
    {
        std::cerr << "Liczba kolumn macierzy A musi byc rowna liczbie wierszy macierzy B!" << std::endl;
    }

    for (INT64 i = 0; i < rowsA; i++)
    {
        delete[] matrixA[i], mulResult[i];
    }

    delete[] matrixA, matrixB;

    //+++++++++++++++++++++++++++++++++++++++++++++++

    std::cout << "---=== MIN Z MACIERZY TROJWYMIAROWEJ ===---\n";
    INT64 rows3D, cols3D, depth;

    std::cout << "Podaj X macierzy 3D: ";
    std::cin >> rows3D;
    std::cout << "Podaj Y macierzy 3D: ";
    std::cin >> cols3D;
    std::cout << "Podaj Z macierzy 3D: ";
    std::cin >> depth;

    INT64*** matrix3D = new INT64** [rows3D];

    for (INT64 i = 0; i < rows3D; i++)
    {
        matrix3D[i] = new INT64* [cols3D];

        for (INT64 j = 0; j < cols3D; j++)
        {
            matrix3D[i][j] = new INT64[depth];
        }
    }

    for (INT64 x = 0; x < rows3D; x++)
    {
        for (INT64 y = 0; y < cols3D; y++)
        {
            for (INT64 z = 0; z < depth; z++)
            {
                printf("[%I64u][%I64u][%I64u]: ", x, y, z);
                std::cin >> matrix3D[x][y][z];
            }
        }
    }

    PrintMatrix3D(matrix3D, rows3D, cols3D, depth);
    INT64 min = MinMatrix3D64(matrix3D, rows3D, cols3D, depth);

    std::cout << "Minimalna wartosc w tej macierzy wynosi: " << min << std::endl;

    for (INT64 i = 0; i < rows3D; i++)
    {
        for (INT64 j = 0; j < cols3D; j++)
        {
            delete[] matrix3D[i][j];
        }
        delete[] matrix3D[i];
    }
    delete[] matrix3D;

    system("pause");
}

void PrintMatrix2D(INT64** matrix, INT64 rows, INT64 cols)
{
    for (INT64 x = 0; x < rows; x++)
    {
        for (INT64 y = 0; y < cols; y++)
        {
            std::cout << matrix[x][y] << " ";
        }
        std::cout << std::endl;
    }
}
void PrintMatrix3D(INT64*** matrix, INT64 rows, INT64 cols, INT64 depth)
{
    for (INT64 x = 0; x < rows; x++)
    {
        for (INT64 y = 0; y < cols; y++)
        {
            for (INT64 z = 0; z < depth; z++)
            {
                std::cout << matrix[x][y][z] << " ";
            }
        }
        std::cout << std::endl;
    }
}