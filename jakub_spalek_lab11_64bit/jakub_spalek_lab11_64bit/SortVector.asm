_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC SortVector		;(int* vector, int n)
SortVector PROC uses rdi rsi 
    
    mov rsi, rdx                    ; iterator 
    dec rsi                         ; przej�cie na ostatni element
    mov rdx, rcx                    ; adres wektora

MainLoop:
    mov rdi, rsi
    dec rdi                         ; index poprzedzaj�cego elementu
    mov rax, [rdx + rsi * 8]        ; aktualny element

    InsideLoop:
        cmp rax, [rdx + rdi * 8]    ; por�wnanie aktualnego z poprzedzaj�cym
        jae MoveNext                ; je�li vector[i] >= vector[i-1] to skacz do MoveNext

        xchg rax, [rdx + rdi * 8]   
        mov [rdx + rsi * 8], rax    ; zamieniamy miejscami vector[i] i vector[i-1]

    MoveNext:
        dec rdi
        jns InsideLoop              ; p�tla wewn�trzna

    dec rsi
    jnz MainLoop                    ; p�tla g�wna
    ret
SortVector ENDP

_TEXT ENDS
END