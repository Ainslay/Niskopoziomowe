_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC AsmMultiplyMatrices64		;(float** matrixA, float** matrixB, float** result int rowsA, int rowsB, int colsB)
AsmMultiplyMatrices64 PROC uses rdi rsi rbx, matrixA:ptr , matrixB:ptr, result:ptr, rowsA:qword , rowsB:qword , colsB:qword
	    
		mov matrixA, rcx
		mov matrixB, rdx
		mov result, r8
		mov rowsA, r9

		mov rcx, rowsA										; iterator i

		LoopI :
			mov rdi, matrixA								; adres macierzy A
			mov rbx, result									; adres macierzy wynikowej
												
			mov rdi, qword ptr [rdi + 4 * rcx - 4]			; matrixA[i]
			mov rbx, qword ptr [rbx + 4 * rcx - 4]			; result[i]
												
			push rcx										; zabezpieczamy i
			mov rcx, colsB									; iterator j
												
			LoopJ :									
												
				mov rdx, rowsB								; iterator k
				fldz										; [s]
												
				LoopK :								
					mov rsi, matrixB						; adres macierzy B
					mov rsi, qword ptr [rsi + 4 * rdx - 4]	; matrixB[k]
												
					fld qword ptr [rdi + 4 * rdx - 4]		; [matrixA[i][k] : s]
					fld qword ptr [rsi + 4 * rcx - 4]		; [matrixB[k][j] : matrixA[i][k] : s]
					fmulp st(1), st							; [matrixB[k][j] * matrixA[i][k] : s]
					faddp st(1), st							; [s + matrixB[k][j] * matrixA[i][k]]
												
					dec rdx							
					jnz LoopK						; dopóki k > 0 skacz do LoopK
												
				fstp qword ptr [rbx + 4 * rcx - 4]				; zapisanie wyniku mno¿enia do result[i][j]
												
				Loop LoopJ							; dopóki j > 0 skacz do LoopK
												
				pop rcx								
		Loop LoopI									; dopóki i > 0 skacz do LoopK

		movd xmm0, result

        ret
AsmMultiplyMatrices64 ENDP

_TEXT ENDS
END