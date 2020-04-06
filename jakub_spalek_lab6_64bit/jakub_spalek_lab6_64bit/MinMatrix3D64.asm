_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC MinMatrix3D64 ;(INT64*** matrix, INT64 rows, INT64 cols, INT64 depth)
MinMatrix3D64 PROC uses rsi rbx , matrix:ptr, rows:qword, cols:qword, depth:qword
					 ; rcx, rdx, r8, r9

    mov r10, rdx                    ; rows
    mov r11, rcx                    ; adres macierzy
    mov rcx, rdx                    ; przygotowanie iteratora i dla for1
        
    mov rdx, [r11 + 8 * rcx - 8]    ; matrix[rows-1]
    mov rdx, [rdx + 8 * rcx - 8]    ; matrix[cols-1]
    mov rax, [rdx + 8 * rcx - 8]    ; rax = matrix[depth-1] - zapisanie ostatniej wartoœci jako minimalnej

    for1:
        mov rsi, r11
        mov rdx, [rsi + 8 * rcx - 8]    ; matrix[i]

        push rcx                        ; i = [rsp]
        mov rcx, r8                     ; przygotowanie iteratora j dla for2

        for2:
            mov rsi, rdx
            mov rsi, [rsi + 8 * rcx - 8]    ; matrix[i][j]
                
            push rcx            ; i = [rsp-4] j = [rsp]
            mov rcx, r9         ; przygotowanie iteratora k dla for3
                
            for3:
                mov rbx , [rsi + 8 * rcx - 8]
                    
                cmp rax, rbx                ; porównaj min z matrix[i][j][k]
                cmovg rax, rbx              ; je¿eli matrix[i][j][k] < min to min = matrix[i][j][k]
                loop for3                   ; dopoki k > 0 skacz do for3
            pop rcx
            loop for2           ; dopoki j > 0 skacz do for2
        pop rcx
        loop for1               ; dopoki i > 0 skacz do for1
               
    mov rax, rax                ; zapisanie wyniku
	
    ret
MinMatrix3D64 ENDP

_TEXT ENDS
END