#include <iostream>

using namespace std;

void PrintBCD(char* BCD, int digitCount);
void GetInput(char* BCD, int digitCount);
char* SumBCD(char* first, char* second, int digitCount);
char* MultiplyBCD(char* first, char* second, int digitCount);

int main()
{
    int digitCount = 0;

    cout << "Podaj liczbe cyfr: ";
    cin >> digitCount;

    digitCount++;

    char* firstBCD = new char[digitCount];
    char* secondBCD = new char[digitCount];
    
    cout << "Podaj pierwsza liczbe:\n";
    GetInput(firstBCD, digitCount);

    cout << "Podaj druga liczbe:\n";
    GetInput(secondBCD, digitCount);

    char* sumResult = SumBCD(firstBCD, secondBCD, digitCount);
    cout << "Ich suma: ";
    PrintBCD(sumResult, digitCount);
    //char* multiplyResult =  MultiplyBCD(firstBCD, secondBCD, digitCount);

    system("pause");

    delete[] firstBCD, secondBCD, sumResult;// , multiplyResult;
}

char* SumBCD(char* first, char* second, int digitCount)
{
    char* result = new char[digitCount];

    __asm
    {
        push edi
        push esi
        push ebx

        mov ecx, digitCount      // przygotowanie iteratora, liczba elementow do sumowania
        
        mov edi, first           // adres pierwszej liczby
        add edi, ecx             // przesuniêcie adresu 
        dec edi                  // na ostatni element   

        mov esi, second          // adres drugiej liczby
        add esi, ecx             // przesuniêcie adresu
        dec esi                  // na ostatni element 

        mov ebx, result          // adres wyniku
        add ebx, ecx             // przesuniêcie adresu
        dec ebx                  // na ostatni element   

        mov ax, 0
        add al, al               // CF = 0

        Sum:
            mov al, [esi]        // al = second[digitCount - 1]
            adc al, ds:[edi]     // al += [edi] + CF
            mov ah, 0            // wyzerowanie przeniesienia
            aaa                  // ah += nowe przeniesienie
            
            mov ds:[ebx], al     // zapisanie wyniku dodawnia first[digitCount - 1] = al

            dec esi              // przesuniêcie adresów na starszy bit
            dec edi
            dec ebx
            dec ecx
            jnz Sum          // dopiki ecx > 0 skacz do SumBCD

        pop ebx
        pop esi
        pop edi
    }

    return result;
}

char* MultiplyBCD(char* first, char* second, int digitCount)
{
    char* result = new char[digitCount * 2];
    char* buffer = new char[digitCount + 1];

    __asm
    {

    }

    delete[] buffer;
    return result;
}

void PrintBCD(char* BCD, int digitCount)
{
    for (int i = 0; i < digitCount; i++)
    {
        printf("%i", (int)BCD[i]);
    }
    cout << endl;
}

void GetInput(char* BCD, int digitCount)
{
    BCD[0] = 0;
    for (int i = 1; i < digitCount; i++)
    {
        printf("[%i]:", i);
        cin >> BCD[i];
    }
}