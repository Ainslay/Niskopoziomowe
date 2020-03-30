_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

PUBLIC if_4
    if_4 PROC int a (rcx), int b (rdx)
        mov  rax, 0     ; zmienna wynikowa (rax)
        cmp  rcx, rdx   ; porownaj zmienne a i b
        jl   else1      ; jesli b jest mniejsze to przejdz do else1
        imul rcx, rcx   ; pomnoz a * a
        add  rcx, rdx   ; dodaj b
        mov  rax, rcx   ; wpisz do wyniku (rax)
        ret;            ; powrot z podprogramu

    else1:
        imul rcx,rcx    ; pomnoz a * a
        sub  rcx,rdx    ; odejmij  
        mov  rax,rcx    ; wpisz do wyniku (rax)
        
        ret;            ; powrot z podprogramu

    if_4 ENDP

_TEXT ENDS 
END