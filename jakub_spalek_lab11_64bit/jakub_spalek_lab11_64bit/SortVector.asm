_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC SortVector		;(int* vector, int n)
SortVector PROC uses rdi rsi 
    
    mov rsi, rdx                    ; iterator 
    dec rsi                         ; przejœcie na ostatni element
    mov rdx, rcx                    ; adres wektora

MainLoop:
    mov rdi, rsi
    dec rdi                         ; index poprzedzaj¹cego elementu
    mov rax, [rdx + rsi * 8]        ; aktualny element

    InsideLoop:
        cmp rax, [rdx + rdi * 8]    ; porównanie aktualnego z poprzedzaj¹cym
        jae MoveNext                ; jeœli vector[i] >= vector[i-1] to skacz do MoveNext

        xchg rax, [rdx + rdi * 8]   
        mov [rdx + rsi * 8], rax    ; zamieniamy miejscami vector[i] i vector[i-1]

    MoveNext:
        dec rdi
        jns InsideLoop              ; pêtla wewnêtrzna

    dec rsi
    jnz MainLoop                    ; pêtla gówna
    ret
SortVector ENDP

_TEXT ENDS
END