_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC SumujElementyTablicy64
    SumujElementyTablicy64 PROC             ; (_int64 n, _int64* tab)
        
       ;push rbx                            ; przygotowanie rejestrow do pracy
       ; push rcx

        xor rax, rax                        ; zerowanie wyniku sumowania
        ;mov rcx, n                          ; przygotowanie iteratora
        ;mov rbx, tab                        ; pobranie adresu tablicy

        Suma :
            add  rax, [rbx + 8 * rcx - 8]   ; eax += el_tablicy
            loop Suma                       ; dopoki ecx > 0 skocz do Suma
            ;mov  sum, rax                   ; zapisanie wyniku

        pop rcx                             ; przywrocenie stanu rejestrow
        pop rbx

        ret                            ; zwroc wynik sumowania
    SumujElementyTablicy64 ENDP
_TEXT ENDS
END