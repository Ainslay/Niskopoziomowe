#include <iostream>

int SumMatrix(int** matrix, int n1, int n2);
int* Multiply(int** matrix, int* vector, int rows, int cols);

int main()
{
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

    std::cout << "Suma elementow tej macierzy: " << SumMatrix(matrix, rows, cols) << std::endl;

    std::cout << "Podaj wektor do mnozenia:\n";

    for (int i = 0; i < cols; i++)
    {
        printf("[%d]: ", i);
        std::cin >> vector[i];
    }

    std::cout << "Wynik mnozenia macierzy i wektora:\n";
    
    multiplicationResult = Multiply(matrix, vector, rows, cols);

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

int SumMatrix(int** matrix, int rows, int cols)
{
    int sum = 0;

    __asm {
        push esi
        push ebx
        push edi

        mov esi, matrix     // adres macierzy
        mov ecx, rows       // wiersze (x)
        mov ebx, cols       // kolumny (y)
        xor eax, eax        // suma

        first:
            mov edi, [esi + 4 * ecx - 4]
            mov ebx, cols

            second:
                add eax, [edi + 4 * ebx - 4]    // matrix[x][y]
                dec ebx
                jnz second  // dopiki ebx > 0 skocz do second
            

            loop first      // dopóki ecx > 0 skocz do first

        mov sum, eax        // zapisanie do wyniku

        pop edi
        pop ebx
        pop esi
    }

    return sum;
}

int* Multiply(int** matrix, int* vector, int rows, int cols)
{
    int* result = new int[cols];
    
    __asm{
        push edi
        push ebx
        push esi

        mov esi, matrix     // adres macierzy
        mov edi, vector     // adres wektora
        mov ebx, result     // adres wyniku
        mov ecx, rows       // wiersze (x)

        first:
            mov esi, matrix                 // adres macierzy
            mov esi, [esi + 4 * ecx - 4]    // ostatni wiersz macierzy

            push ecx
            push ebx
            
            mov ebx, 0
            mov ecx, cols     // kolumny (y)

            second:
                mov  eax, [esi + 4 * ecx - 4]    // matrix[x][y]
                imul eax, [edi + 4 * ecx - 4]    // matrix[x][y] * vector[x]
                add  ebx, eax                    // result[x] + eax
                loop second
            mov eax, ebx                         // wynik pêtli wewnêtrznej
            pop ebx
            pop ecx

            mov [ebx + 4 * ecx - 4], eax
            loop first
        
        pop esi
        pop ebx
        pop edi
    }

    return result;
}