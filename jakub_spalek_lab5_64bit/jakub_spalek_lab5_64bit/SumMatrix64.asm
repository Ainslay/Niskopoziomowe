_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC SumMatrix64						;(INT64** matrix, INT64 rows, INT64 cols)
	SumMatrix64 PROC uses rsi rdi		;(rcx)(rdx)(r8)
	
		xor rax, rax				; suma
	first:
		mov rsi, [rcx + 8*rdx - 8]  ; adres wiersza
		mov r10, r8					; kolumny
	
		second:
			add rax, [rsi + 8*r10 - 8]
			dec r10
			jnz second

		dec rdx					
		jnz first					; dopoki rcx > 0 skocz do first
	ret

	SumMatrix64 ENDP
_TEXT ENDS
END