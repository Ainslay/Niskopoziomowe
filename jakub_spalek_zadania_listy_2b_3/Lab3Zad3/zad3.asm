_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC case_2
case_2 PROC ; int x (rcx), int op (rdx)
    mov rax, 0          ; zmienna wynikowa
    cmp rdx, 0          
    je case0            ; jesli op == 0 skocz do case0
    cmp rdx, 1
    je case1            ; jesli op == 1 skocz do case1
    cmp rdx, 2          
    je case2            ; jesli op == 2 skocz do case2
    jmp case_default    ; jesli zadne z powyzszych nie jest spelnione, skocz do case_default
        
case0:
    imul rcx,rcx        ; pomnoz x * x
    jmp break           ; skocz do break
case1:
    mov rax, rcx        ; wpisz x do rax
    sub rax, 3          ; x - 3
    imul rcx, rax       ; x * (x - 3)
    jmp break           ; skocz do break
case2:
    mov rax, rcx        ; wpisz x do rax
    sub rax, 5          ; x - 5
    imul rcx,rax        ; x * (x - 5)
    jmp break           ; skocz do break
case_default:
    mov rax,0           ; wpisz do wyniku 0
    ret                 ; powrot z podprogramu
break:
    mov rax,rcx         ; wpisz wynik operacji do rax
    ret                 ; powrot z podprogramu

case_2 ENDP
_TEXT ENDS 
END