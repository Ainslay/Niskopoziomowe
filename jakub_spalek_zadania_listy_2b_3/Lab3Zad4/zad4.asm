_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC silnia_for_jnz
	silnia_for_jnz PROC		; int n (rcx) - iterator i
		mov rax, 1			; silnia = 1

	loop1:
		imul rax, rcx 		; silnia = silnia * i
		dec rcx				; i--
		jnz loop1			; jesli iterator wiekszy od 0 skocz do loop1

		ret;				; powrot z podprogramu
	silnia_for_jnz ENDP

PUBLIC silnia_for_loop
	silnia_for_loop PROC	; int n (rcx) - iterator i
		mov rax, 1			; silnia = 1

	jump:
		imul rax, rcx 		; silnia = silnia * i
		loop jump			; dekrementuj iterator, jesli wiekszy od 0 to skocz do jump

		ret;
silnia_for_loop ENDP

_TEXT ENDS
END