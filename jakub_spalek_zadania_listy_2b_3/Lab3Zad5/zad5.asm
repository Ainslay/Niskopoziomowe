_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC petla_while
    petla_while PROC     ; int n (rcx)

    mov  rax,0           ; zmienna wynikowa
    mov  rdx, 1          ; ustaw iterator na 1
    imul rcx,2           ; n * 2
    
jump:
    add rax, rdx         ; dodaj do wyniku (rax) iterator (rdx)
    inc rdx              ; i++
    cmp rdx, rcx         
    jle jump             ; jesli i <= 2*n (rdx <= rcx) skocz do jump
    ret                  ; powrot z podprogramu

    petla_while ENDP   
    
_TEXT ENDS 
END