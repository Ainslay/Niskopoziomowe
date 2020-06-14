_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC Task4_64	             ;(double* x, double* z, int N)
Task4_64 PROC uses rsi rdi, x:qword ; rcx, rdx, r8

        mov rsi, rcx                          ; adres drugiego wektora
        mov rdi, rdx                          ; adres pierwszego wektora
        mov rcx, r8                           ; iterator
        fldz                                  ; przeniesienie zera na stos   [s]
                                              
    Sum:                                      
        fld  qword ptr [rsi + 8 * rcx - 8]    ; x[ecx-1]                     [x : s]
        fmul qword ptr [rdi + 8 * rcx - 8]    ; x[ecx-1] * z[ecx-1]          [x*z : s]
        faddp st(1), st                       ; st(1) = s + x*z              [s]
    Loop Sum                                  ; dopóki ecx > 0 skacz do Sum
                                              
        fstp x                                ; zapis do wyniku, x = st(0)   [stos pusty]

        movq xMM0, x

        ret
Task4_64 ENDP

_TEXT ENDS
END