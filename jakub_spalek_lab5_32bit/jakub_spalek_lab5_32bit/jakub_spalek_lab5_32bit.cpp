#include <iostream>

int SumMatrix(int** matrix, int n1, int n2);
int* Multiply(int** matrix, int* vector, int n1, int n2);

int main()
{
    int** matrix;
    int* vector;
    int* multiplicationResult;
    int n1, n2;

    std::cout << "Podaj liczbe kolumn: ";
    std::cin >> n1;
    std::cout << "Podaj liczbe wierszy: ";
    std::cin >> n2;

    matrix = new int* [n1];
    vector = new int[n1];

    for (int i = 0; i < n1; i++)
    {
        matrix[i] = new int[n2];
    }

    for (int x = 0; x < n1; x++)
    {
        for (int y = 0; y < n2; y++)
        {
            printf("[%d][%d]: ", x, y);
            std::cin >> matrix[x][y];
        }
    }

    std::cout << "Suma elementow tej macierzy: " << SumMatrix(matrix, n1, n2) << std::endl;

    std::cout << "Podaj wektor do mnozenia:\n";

    for (int i = 0; i < n1; i++)
    {
        printf("[%d]: ", i);
        std::cin >> vector[i];
    }

    std::cout << "Wynik mno¿enia macierzy i wektora:\n";
    
    multiplicationResult = Multiply(matrix, vector, n1, n2);

    for (int i = 0; i < n1; i++)
    {
        printf("[%d]: %d", i, multiplicationResult[i]);
        std::cout << std::endl;
    }

    system("pause");

    for (int i = 0; i < n1; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix, vector, multiplicationResult;
}

int SumMatrix(int** matrix, int n1, int n2)
{
    int sum = 0;

    __asm {
        push esi
        push ebx
        push edi

        mov esi, matrix     // adres macierzy
        mov ecx, n1         // kolumny (x)
        mov ebx, n2         // wiersze (y)
        xor eax, eax        // suma

        first:
            mov edi, [esi + 4 * ecx - 4]
            mov ebx, n2

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

int* Multiply(int** matrix, int* vector, int n1, int n2)
{
    int* result = new int[n1];
    
    __asm{
        push edi
        push ebx
        push esi

        mov esi, matrix     // adres macierzy
        mov edi, vector     // adres wektora
        mov ebx, result     // adres wyniku
        mov ecx, n2         // wiersze (y)

        first:
            mov esi, matrix                 // adres macierzy
            mov esi, [esi + 4 * ecx - 4]    // ostatni wiersz macierzy

            push ecx
            push ebx
            
            mov ebx, 0
            mov ecx, n1     // kolumny (x)

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