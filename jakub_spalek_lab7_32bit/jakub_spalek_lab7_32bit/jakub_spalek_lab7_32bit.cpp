#include <iostream>

using namespace std;

void PrintBCD(char* BCD, int digitCount);
void GetSumInput(char* BCD, int digitCount);
void GetMulInput(char* BCD, int digitCount);
char* SumBCD(char* first, char* second, int digitCount);
char* MultiplyBCD(char* first, char* second, int digitCount);

void Task1();
void Task2();

int main()
{
    Task1();
    Task2();
}

void Task1()
{
    cout << "---=== ZADANIE 1 ===---\n\n";
    int digitCount = 0;

    cout << "Podaj liczbe cyfr: ";
    cin >> digitCount;

    digitCount++;

    char* firstBCD = new char[digitCount];
    char* secondBCD = new char[digitCount];

    cout << "Podaj pierwsza liczbe:\n";
    GetSumInput(firstBCD, digitCount);

    cout << "Podaj druga liczbe:\n";
    GetSumInput(secondBCD, digitCount);

    char* sumResult = SumBCD(firstBCD, secondBCD, digitCount);
    cout << "Ich suma: ";
    PrintBCD(sumResult, digitCount);

    delete[] firstBCD, secondBCD, sumResult;

    system("pause");
    system("cls");
}

void Task2()
{
    cout << "---=== ZADANIE 2 ===---\n\n";
    int digitCount = 0;

    cout << "Podaj liczbe cyfr: ";
    cin >> digitCount;

    char* firstBCD = new char[digitCount];
    char* secondBCD = new char[digitCount];

    cout << "Podaj pierwsza liczbe:\n";
    GetMulInput(firstBCD, digitCount);

    cout << "Podaj druga liczbe:\n";
    GetMulInput(secondBCD, digitCount);

    char* mulResult = MultiplyBCD(firstBCD, secondBCD, digitCount);
    cout << "Ich iloczyn: ";
    PrintBCD(mulResult, digitCount * 2);

    delete[] firstBCD, secondBCD, mulResult;

    system("pause");
    system("cls");
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

            dec esi              // przesuniêcie adresów na poprzedni element
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
        push edi
        push esi
        push ebx

        mov ecx, digitCount         // przygotowanie iteratora, liczba elementow do sumowania

        mov edi, second             // adres drugiej liczby
        add edi, ecx                // przesuniêcie adresu 
        dec edi                     // na ostatni element   
        
        mov ebx, result             // adres wyniku

        // Zerowanie tablicy wynikowej
        add ecx, ecx                // rozmiar wyniku (digitCount * 2)
        add ebx, ecx                // przesuniêcie adresu
        dec ebx                     // na ostatni element 
        xor ax, ax

        Zero:
            mov [ebx], al           // result[i] = 0
            dec ebx                 // poprzedni element
        Loop Zero                   // dopóki ecx > 0 skacz do Zero

        // Odtowrzenie rejestrów po zerowaniu tablicy
        mov ecx, digitCount
        mov ebx, result
        add ebx, ecx
        add ebx, ecx
        dec ebx

        MainLoop:
            push ecx                    // zabezpieczenie zewnêtrznego iteratora

            mov ecx, digitCount         // iterator dla pêtli Multiply
            mov esi, first              // adres pierwszej liczby
            mov al, 0
            add al, al                  // CF = 0

            Multiply:
                mov al, ds:[esi]
                mul ds:[edi]            // first[i] *= second[i]
                aam                     // korekta po mno¿eniu
                push ax                 // wynik mno¿enia na stos
                inc esi                 // przesuniêcie pierwszej liczby na nastêpny element
            Loop Multiply               // dopóki ecx > 0 skacz do Multiply

            mov ecx, digitCount         // iterator dla pêtli Sum
            mov dh, 0                   // przeniesienie = 0
        
            mov esi, buffer             // tablica pomocnicza, przechowuje wynik sumowania po mno¿eniu
            add esi, ecx                // przesuniêcie adresu na ostatni element 

            mov ax, 0
            add al, al                  // CF = 0

            Sum:
                pop ax                  // wynik z mno¿enia
                add al, dh              // przeniesienie z poprzedniej pozycji
                mov dh, ah              // zapamiêtanie przeniesienia z mno¿enia
                mov ah, 0
                aaa                     // korekta po sumowaniu ah += przeniesienie
            
                add dh, ah              // dodanie przeniesienia z sumowania
                mov [esi], al           // zapis wyniku do tablicy pomocniczej buffer
                dec esi                 // poprzedni element buffer
            Loop Sum                    // dopóki ecx > 0 skacz do Sum

            mov [esi], dh               // najstarsze przeniesienie

            mov esi, buffer             // tablica pomocnicza
            mov ecx, digitCount         // iterator
            add esi, ecx                // przesuniêcie adresu na ostatni element
            inc ecx                     // digitCount + 1 elementów w buffer
            mov ax, 0
            push ebx                    // zabezpiecz wynik
            add al, al                  // CF = 0

            SumBuffer:
                mov al, [esi]           // al = buffer[i]
                adc al, [ebx]           // al += result[i] + CF
                mov ah, 0
                aaa                     // korekta po sumowaniu ah += przeniesienie
                mov [ebx], al           // result[i] = al

                dec ebx                 // poprzedni element
                dec esi
            Loop SumBuffer              // dopoki ecx > 0 skacz do SumBuffer

            dec edi
            pop ebx
            dec ebx
            pop ecx
        Loop MainLoop                   // dopoki ecx > 0 skacz do MainLoop

        pop ebx
        pop esi
        pop edi
    }

    delete[] buffer;
    return result;
}

void PrintBCD(char* BCD, int digitCount)
{
    int i = 0;
    if (BCD[0] == 0) i = 1;

    for (i; i < digitCount; i++)
    {
        printf("%i", (int)BCD[i]);
    }
    cout << endl;
}

void GetSumInput(char* BCD, int digitCount)
{
    int tmp = 0;
    BCD[0] = 0;
    for (int i = 1; i < digitCount; i++)
    {
        printf("[%i]:", i);
        cin >> tmp;
        BCD[i] = tmp;
    }
}

void GetMulInput(char* BCD, int digitCount)
{
    int tmp = 0;

    for (int i = 0; i < digitCount; i++)
    {
        printf("[%i]:", i);
        cin >> tmp;
        BCD[i] = tmp;
    }
}