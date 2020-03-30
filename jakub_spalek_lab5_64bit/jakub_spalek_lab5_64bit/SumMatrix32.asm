_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC SumMatrix32					;(int** matrix, int rows, int cols)
	SumMatrix32 PROC uses rsi rdi 	;(rcx)(rdx)(r8)

		xor rax, rax				; suma
	first:
		mov rsi, [rcx + 8*rdx - 8]  ; adres wiersza
		mov r10, r8				; kolumny
		
		second:
			movsxd r11, dword ptr[rsi + 4*r10 - 4]
			add rax, r11
			dec r10
			jnz second
	
	dec rdx
	jnz first

	ret
	SumMatrix32 ENDP
_TEXT ENDS
END