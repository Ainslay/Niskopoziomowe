#include <iostream>

void SumMatrices(int** matrixA, int** matrixB, int** result, int rows, int cols);
void MultiplyMatrices(int** matrixA, int** matrixB, int** result, int rowsA, int colsA, int colsB);
int MinMatrix3D(int*** matrix, int rows, int cols, int depth);
void PrintMatrix2D(int** matrix, int rows, int cols);

int main()
{
    int** matrixA;
    int** matrixB;
    int** sumResult;
    int rowsA, colsA;
    int rowsB, colsB;

    std::cout << "---=== SUMOWANIE ===---\n";
    std::cout << "Podaj liczbe wierszy: ";
    std::cin >> rowsA;
    std::cout << "Podaj liczbe  kolumn: ";
    std::cin >> colsA;

    matrixA = new int* [rowsA];
    matrixB = new int* [rowsA];
    sumResult = new int* [rowsA];

    for (int i = 0; i < rowsA; i++)
    {
        matrixA[i] = new int[colsA];
        matrixB[i] = new int[colsA];
        sumResult[i] = new int[colsA];
    }

    std::cout << "Wprowadz macierz A:\n";
    for (int x = 0; x < rowsA; x++)
    {
        for (int y = 0; y < colsA; y++)
        {
            printf("[%d][%d]: ", x, y);
            std::cin >> matrixA[x][y];
        }
    }

    std::cout << "Wprowadz macierz B:\n";
    for (int x = 0; x < rowsA; x++)
    {
        for (int y = 0; y < colsA; y++)
        {
            printf("[%d][%d]: ", x, y);
            std::cin >> matrixB[x][y];
        }
    }

    SumMatrices(matrixA, matrixB, sumResult, rowsA, colsA);
    std::cout << "Wynik sumowania tych macierzy:\n";
    PrintMatrix2D(sumResult, rowsA, colsA);

    for (int i = 0; i < rowsA; i++)
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

    matrixA = new int* [rowsA];

    for (int i = 0; i < rowsA; i++)
    {
        matrixA[i] = new int[colsA];
    }

    std::cout << "Wprowadz macierz A:\n";
    for (int x = 0; x < rowsA; x++)
    {
        for (int y = 0; y < colsA; y++)
        {
            printf("[%d][%d]: ", x, y);
            std::cin >> matrixA[x][y];
        }
    }

    std::cout << "Podaj liczbe wierszy macierzy B: ";
    std::cin >> rowsB;
    std::cout << "Podaj liczbe  kolumn macierzy B: ";
    std::cin >> colsB;
    
    int** mulResult = new int* [rowsA];

    for (int i = 0; i < rowsA; i++)
    {
        mulResult[i] = new int[colsB];
    }

    if (colsA == rowsB)
    {
        matrixB = new int* [rowsB];

        for (int i = 0; i < rowsB; i++)
        {
            matrixB[i] = new int[colsB];
        }

        std::cout << "Wprowadz macierz B:\n";
        for (int x = 0; x < rowsB; x++)
        {
            for (int y = 0; y < colsB; y++)
            {
                printf("[%d][%d]: ", x, y);
                std::cin >> matrixB[x][y];
            }
        }

        MultiplyMatrices(matrixA, matrixB, mulResult, rowsA, colsA, colsB);
        
        std::cout << "Wynik mnozenia tych dwoch macierzy:\n";
        PrintMatrix2D(mulResult, rowsA, colsB);

        for (int i = 0; i < rowsB; i++)
        {
            delete[] matrixB[i];
        }
    }
    else
    {
        std::cerr << "Liczba kolumn macierzy A musi byc rowna liczbie wierszy macierzy B!" << std::endl;
    }

    for (int i = 0; i < rowsA; i++)
    {
        delete[] matrixA[i], mulResult[i];
    }

    delete[] matrixA, matrixB;

    system("pause");
}

void SumMatrices(int** matrixA, int** matrixB, int** result, int rows, int cols)
{
    __asm {

        push esi
        push ebx
        push edi

        mov esi, matrixA
        mov edi, matrixB
        mov ebx, result
        mov ecx, rows

        rowsLoop:
            push ecx        // zabepiecz ecx na stosie
            push esi
            push edi
            push ebx
            
            mov esi, [esi + 4 * ecx - 4]    // ustawienie adresów wierszy macierzy
            mov edi, [edi + 4 * ecx - 4]
            mov ebx, [ebx + 4 * ecx - 4]
            mov ecx, cols   // ustawienie iteratora na liczbe kolumn
            
            colsLoop:
                xor eax, eax
                add eax, [esi + 4 * ecx - 4]
                add eax, [edi + 4 * ecx - 4] // TUTAJ
                mov [ebx + 4 * ecx - 4], eax
                loop colsLoop   // dopóki ecx > 0 skacz do cols
                
                pop ebx     // zdejmij rejestry ze stosu
                pop edi
                pop esi
                pop ecx

            loop rowsLoop       // dopóki ecx > 0 skacz do rows
            
        pop edi
        pop ebx
        pop esi
    }
    
}

void MultiplyMatrices(int** matrixA, int** matrixB, int** result, int rowsA, int colsA, int colsB)
{

}

void PrintMatrix2D(int** matrix, int rows, int cols)
{
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            std::cout << matrix[x][y] << " ";
        }
        std::cout << std::endl;
    }
}