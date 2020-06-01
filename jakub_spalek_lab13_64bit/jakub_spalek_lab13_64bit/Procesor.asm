_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC Procesor	;(INT64* vec1, INT64* vec2, INT64* result, INT64 n)
Procesor PROC uses rdi rsi rbx  ; rcx, rdx, r8, r9

    mov rdi, rcx                        ; adres pierwszego wektora
    mov rsi, rdx                        ; adres drugiego wektora
    mov rbx, r8                         ; adres wektora wynikowego
    mov rcx, r9                         ; rozmiar (iterator i)

    MainLoop:
        mov rax, [rdi + rcx * 8 - 8]    ; rax = vec1[i]
        sub rax, [rsi + rcx * 8 - 8]    ; rax = rax - vec2[i]
        mov [rbx + rcx * 8 - 8], rax    ; zapis wyniku do result[i]
    Loop MainLoop                       ; dopóki rcx > 0 skacz do MainLoop

    ret

Procesor ENDP

_TEXT ENDS
END