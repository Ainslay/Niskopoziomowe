_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC SumMatrices64 ;(INT64** matrixA, INT64** matrixB, INT64** result, INT64 rows, INT64 cols)
SumMatrices64 PROC uses rsi rbx rdi, matrixA:ptr, matrixB:ptr, result:ptr, rows:qword, cols:qword
					; rcx, rdx, r8, r9

        mov rsi, rcx        ; zapisanie adresów macierzy w rejestrach
        mov rdi, rdx
        mov rbx, r8
        mov rcx, r9           ; ustawinenie iteratora i

        rowsLoop:
            push rcx            ; zabepiecz rejestry na stosie
            push rsi
            push rdi
            push rbx
            
            mov rsi, [rsi + 8 * rcx - 8]    ; ustawienie adresów wierszy macierzy
            mov rdi, [rdi + 8 * rcx - 8]
            mov rbx, [rbx + 8 * rcx - 8]
            mov rcx, cols                   ; ustawienie iteratora j
            
            colsLoop:
                xor rax, rax
                add rax, [rsi + 8 * rcx - 8]    ; rax += matrixA[i][j]
                add rax, [rdi + 8 * rcx - 8]    ; rax += matrixB[i][j]
                mov [rbx + 8 * rcx - 8], rax    ; result[i][j] = rax
                loop colsLoop               ; dopóki rcx > 0 skacz do cols
                
            pop rbx                     ; zdejmij rejestry ze stosu
            pop rdi
            pop rsi
            pop rcx

            loop rowsLoop       ; dopóki rcx > 0 skacz do rows

        ret
SumMatrices64 ENDP

_TEXT ENDS
END