_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC MultiplyMatrices64 ;(int** matrixA, int** matrixB, int** result, int rowsA, int colsA, int colsB)
MultiplyMatrices64 PROC uses rsi rbx rdi, matrixA:ptr, matrixB:ptr, result:ptr, rowsA:qword, colsA:qword, colsB:qword
					; rcx, rdx, r8, r9, stack
        
        mov r10, rdx 
        mov rdx, rcx
        mov rcx, r9              ; przygotowanie iteratora n1 dla for1
        mov r9, colsA
        mov r11, colsB

        for1:
            push rcx
            mov rcx, r11         ; przygotowanie iteratora n3 dla for3

            for3:
                mov rbx, 0
                mov rsi, rdx
                mov rax, [rsp]                  ; wpisanie do rax rowsA
                mov rsi, [rsi + 8 * rax - 8]    ; matrixA [n1]

                push rcx
                mov rcx, r9
                for2:
                    mov rdi, r10
                    mov rax, [rsp]                  ; wpisanie do rax colsB
                    mov rdi, [rdi + 8 * rcx - 8]    ; matrixB[n2]
                    mov rax, [rdi + 8 * rax - 8]
                    imul rax, [rsi + 8 * rcx - 8]   ; matrixA[n1][n2] * matrixB[n2][n3]
                    add rbx, rax                    ; edx += matrixA[n1][n2] * matrixB[n2][n3]
                    
                    loop for2                       ; dopoki n2 > 0 skacz do for2
                
                pop rcx
                mov rsi, r8             ; adres macierzy result
                mov rax, [rsp]              ; rax = n1 , pobrane ze stosu

                mov rsi, [rsi + 8 * rax - 8]     ; result[n1]
                mov [rsi + 8 * rcx - 8], rbx     ; result[n1][n3] = rbx
                
            loop for3                   ; dopoki n3 > 0 skacz do for3
            pop rcx
        loop for1                       ; dopoki n1 > 0 skacz do for1

	 ret
MultiplyMatrices64 ENDP

_TEXT ENDS
END