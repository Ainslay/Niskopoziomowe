_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

	PUBLIC if_3
	if_3 PROC
	
		mov rax, 0		; do rax wpisz wartosc 0 (zmienna wynikowa x = 0)
		cmp rcx, rdx	; porownaj rejestry rcx (zmienna a) z rdx (zmienna b)
		jle skip		; jesli jest mniejsze badz rowne pomin
		imul rdx, rdx	; pomnoz b * b (rdx)
		sub rdx, rcx	; odejmij a (rcx)
		mov rax, rdx	; wpisz wynik do zmiennej wynikowej x

	skip:
		ret;			; powrot z podprogramu

	if_3 ENDP
_TEXT ENDS
END