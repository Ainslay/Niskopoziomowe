_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC PrimeNumbers		            ;(INT64* vector, INT64 n)
PrimeNumbers PROC uses rdi rsi rbx 
    
    mov rdi, rcx                    ; adres tablicy
    mov rcx, rdx                    ; n - ile liczb do wyznaczenia
    mov rsi, 0                      ; iterator
    mov rbx, 2                      ; sprawdzana liczba
    mov [rdi + rsi * 8], rbx        ; pierwsza liczba

MainLoop:
    inc rbx                         ; zwi�kszamy liczb� sprawdzan�
    mov r9, rbx
    dec r9                          ; iterator i

    InsideLoop:
        xor rdx, rdx                ; rdx = 0
        mov rax, rbx                
        div r9                      ; sprawdzana / i
        cmp rdx, 0
        je Divides                  ; je�li reszta z dzielenia = 0 skacz do Divides

        dec r9
        cmp r9, 1
        ja InsideLoop               ; dop�ki r9 > 1 skacz do InsideLoop

        mov qword ptr[rdi], rbx     ; zapisanie liczby pierwszej do tablicy
        add rdi, 8                  ; przesuni�cie na nast�pny indeks
        inc rsi                     ; zwi�kszamy iterator p�tli 

Divides:
    cmp rsi, rcx
    jb MainLoop                     ; dop�ki rsi < n skacz do MainLoop

    ret
PrimeNumbers ENDP

_TEXT ENDS
END