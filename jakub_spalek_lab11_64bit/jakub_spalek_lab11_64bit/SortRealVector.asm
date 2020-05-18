_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC SortRealVector		;(float* vector, int n)
SortRealVector PROC uses rdi rsi, clean:dword

	mov rsi, rdx						; iterator 
	dec rsi								; przej�cie na ostatni element
	mov rdx, rcx						; adres wektora
						
MainLoop:
	mov rdi, rsi
	dec rdi								; index poprzedzaj�cego elementu
	
	InsideLoop:
		fld dword ptr [rdx + rsi * 4]	; aktualny element		[vector[i]]
		fld dword ptr [rdx + rdi * 4]	; poprzedni element [vector[i-1] : vector[i]] 
		fcomi st, st(1)					; por�wnanie aktualnego z poprzedzaj�cym
		jb MoveNext						; je�li vector[i-1] < vector[i] to skacz do MoveNext
		fstp dword ptr [rdx + rsi * 4]	; vector[i] = vector[i-1]	[vector[i]]			
		fst dword ptr [rdx + rdi * 4]	; vector[i-1] = vector[i]	[vector[i]]

	MoveNext:
		fstp clean						
		fstp clean						; wyczyszczenie stosu koprocesora
		dec rdi
		jns InsideLoop					; p�tla wewn�trzna

	dec rsi
	jnz MainLoop						; p�tla g��wna

	ret
SortRealVector ENDP

_TEXT ENDS
END