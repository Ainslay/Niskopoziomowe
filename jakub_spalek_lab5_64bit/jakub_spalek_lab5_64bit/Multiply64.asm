_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

.code

Multiply64 proc uses rbx rsi, matrix:ptr, vector:ptr, result:ptr, rows:qword, cols:qword
                                ; rcx, rdx, r8, r9, stack
first:
    mov rsi, [rcx + r9 * 8 - 8]     ; matrix[rows]* ustawiamy siê na ostatni element
    mov rbx, cols                   ; kolumny
    xor r10, r10                    ; suma
    
    second:
        mov rax, [rsi + rbx*8 - 8]  ; rax = matrix[rows][cols]
        imul rax, [rdx + rbx*8 - 8] ; rax *= v[cols]
        add r10, rax
        dec rbx
        jnz second

    mov [r8 + r9*8 - 8], r10
    dec r9
    jnz first

ret
Multiply64 endp

_TEXT ENDS
END