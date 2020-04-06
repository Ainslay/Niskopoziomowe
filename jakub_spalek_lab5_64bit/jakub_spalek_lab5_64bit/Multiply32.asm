_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC Multiply32           ; (int** matrix, int* vector, int* result, int rows, int cols);

    Multiply32 PROC uses rbx rsi, matrix:ptr, vector:ptr, result:ptr, rows:qword, cols:qword
                            ; rcx, rdx, r8, r9, stack
    first:
        mov rsi, [rcx + r9 * 8 - 8]     ; ostatni wiersz macierzy
        movsxd rbx, dword ptr cols      ; kolumny
        xor r10, r10                    ; suma
    
        second:
            movsxd r11, dword ptr[rsi + rbx * 4 - 4]
            mov  rax, r11                ; rax = matrix[rows][cols]
            movsxd r11, dword ptr[rdx + rbx * 4 - 4]
            imul rax, r11 ; rax *= vector[cols]
            add  r10, rax
            dec  rbx
            jnz  second


        mov [r8 + r9 * 4 - 4], r10d      ; podejrzewam, ¿e tu jest problem, liczy w porz¹dku a zapisuje 0 wszedzie poza indeksem [0]
        dec r9
        jnz first

        ret

    Multiply32 endp
_TEXT ENDS
END