// Opracowane przez: Jakub Spa³ek, Aleksandra Pyrkosz, Daniel Wiêcek

#include <iostream>

void SumMatrices(int** matrixA, int** matrixB, int** result, int rows, int cols);
void MultiplyMatrices(int** matrixA, int** matrixB, int** result, int rowsA, int colsA, int colsB);
int MinMatrix3D(int*** matrix, int rows, int cols, int depth);
void PrintMatrix2D(int** matrix, int rows, int cols);
void PrintMatrix3D(int*** matrix, int rows, int cols, int depth);

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

    //+++++++++++++++++++++++++++++++++++++++++++++++

    std::cout << "---=== MIN Z MACIERZY TROJWYMIAROWEJ ===---\n";
    int rows3D, cols3D, depth;

    std::cout << "Podaj X macierzy 3D: ";
    std::cin >> rows3D;
    std::cout << "Podaj Y macierzy 3D: ";
    std::cin >> cols3D;
    std::cout << "Podaj Z macierzy 3D: ";
    std::cin >> depth;

    int*** matrix3D = new int** [rows3D];

    for (int i = 0; i < rows3D; i++)
    {
        matrix3D[i] = new int* [cols3D];

        for (int j = 0; j < cols3D; j++)
        {
            matrix3D[i][j] = new int[depth];
        }
    }
    
    for (int x = 0; x < rows3D; x++)
    {
        for (int y = 0; y < cols3D; y++)
        {
            for (int z = 0; z < depth; z++)
            {
                printf("[%d][%d][%d]: ", x, y, z);
                std::cin >> matrix3D[x][y][z];
            }
        }
    }

    PrintMatrix3D(matrix3D, rows3D, cols3D, depth);
    int min = MinMatrix3D(matrix3D, rows3D, cols3D, depth);

    std::cout << "Minimalna wartosc w tej macierzy wynosi: " << min << std::endl;

    for (int i = 0; i < rows3D; i++)
    {
        for (int j = 0; j < cols3D; j++)
        {
            delete[] matrix3D[i][j];
        }
        delete[] matrix3D[i];
    }
    delete[] matrix3D;

    system("pause");
}

int MinMatrix3D(int*** matrix, int rows, int cols, int depth)
{
    int min = 0;

    __asm {
        push esi
        push ebx
        mov esi, matrix                 // adres macierzy
        mov ecx, rows                   // przygotowanie iteratora i dla for1
        
        mov edx, [esi + 4 * ecx - 4]    // matrix[rows-1]
        mov edx, [edx + 4 * ecx - 4]    // matrix[cols-1]
        mov eax, [edx + 4 * ecx - 4]    // eax = matrix[depth-1] - zapisanie ostatniej wartoœci jako minimalnej
        mov min, eax

        for1:
            mov esi, matrix
            mov edx, [esi + 4 * ecx - 4]    // matrix[i]

            push ecx                // i = [esp]
            mov ecx, cols           // przygotowanie iteratora j dla for2

            for2:
                mov esi, edx
                mov esi, [esi + 4 * ecx - 4]    // matrix[i][j]
                
                push ecx            // i = [esp-4] j = [esp]
                mov ecx, depth      // przygotowanie iteratora k dla for3
                
                for3:
                    mov ebx , [esi + 4 * ecx - 4]
                    
                    cmp eax, ebx                    // porównaj min z matrix[i][j][k]
                    cmovg eax, ebx                  // je¿eli matrix[i][j][k] < min to min = matrix[i][j][k]
                    loop for3                       // dopoki k > 0 skacz do for3
                pop ecx
                loop for2           // dopoki j > 0 skacz do for2
            pop ecx
            loop for1               // dopoki i > 0 skacz do for1
               
        mov min, eax                // zapisanie wyniku
        
        pop ebx
        pop esi
    }

    return min;
}
void SumMatrices(int** matrixA, int** matrixB, int** result, int rows, int cols)
{
    __asm {

        push esi
        push ebx
        push edi

        mov esi, matrixA        // zapisanie adresów macierzy w rejestrach
        mov edi, matrixB
        mov ebx, result
        mov ecx, rows           // ustawinenie iteratora

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
                add eax, [edi + 4 * ecx - 4]
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
    __asm {

        push esi            // zabezpieczenie rejestrów
        push ebx
        push edi

        mov ecx, rowsA      // przygotowanie iteratora n1 dla for1
        
        for1:
            push ecx
            mov ecx, colsB          // przygotowanie iteratora n3 dla for3

            for3:
                mov ebx, 0
                mov esi, matrixA
                mov eax, [esp]      // wpisanie do eax rowsA
                mov esi, [esi + 4 * eax - 4]    // matrixA [n1]

                push ecx
                mov ecx, colsA
                for2:
                    mov edi, matrixB
                    mov eax, [esp]                  // wpisanie do eax colsB
                    mov edi, [edi + 4 * ecx - 4]    // matrixB[n2]
                    mov eax, [edi + 4 * eax - 4]
                    imul eax, [esi + 4 * ecx - 4]    // matrixA[n1][n2] * matrixB[n2][n3]
                    add ebx, eax                    // edx += matrixA[n1][n2] * matrixB[n2][n3]
                    
                    loop for2               // dopoki n2 > 0 skacz do for2
                
                pop ecx
                mov esi, result             // adres macierzy result
                mov eax, [esp]              // eax = n1 , pobrane ze stosu

                mov esi, [esi + 4 * eax - 4]     // result[n1]
                mov [esi + 4 * ecx - 4], ebx     // result[n1][n3] = edx
                
            loop for3           // dopoki n3 > 0 skacz do for3
            pop ecx
        loop for1           // dopoki n1 > 0 skacz do for1

        pop edi
        pop ebx
        pop esi
    }
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
void PrintMatrix3D(int*** matrix, int rows, int cols, int depth)
{
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            for (int z = 0; z < depth; z++)
            {
                std::cout << matrix[x][y][z] << " ";
            }
        }
        std::cout << std::endl;
    }
}