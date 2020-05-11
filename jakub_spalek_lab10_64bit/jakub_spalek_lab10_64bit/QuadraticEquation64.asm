_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC QuadraticEquation64		;(float a, float b, float c, float* roots)
QuadraticEquation64 PROC , a:qword , b:qword , c:qword, delta:qword

		fld b					; [b]
		fld st					; [b : b]
		fmulp st(1), st			; [b^2]
								;
		fld a					; [a : b^2]
		fld1					; [1 : a : b^2]	
		fld1					; [1 : 1 : a : b^2]
		fadd					; [2 : a : b^2]
		fld st					; [2 : 2 : a : b^2]
		fadd					; [4 : a : b^2]
		fmul					; [4a : b^2]
		fmul c					; [4ac : b^2]
		fsubp st(1), st			; [b^2-4ac] obliczona delta
								;
		fst delta				;
		cmp delta, 0 			; porównanie delty i 0
		ja Greater				; jeœli delta > 0 skacz do greater
		je Equal				; jeœli delta = 0 skacz do equal
		jb Below				; jeœli delta < 0 skacz do below

		Greater:
			fsqrt				; [sqrt(delta)]
								;
			fld b				; [b : sqrt(delta)]
			fchs				; [-b : sqrt(delta)]
			fld st				; [-b : -b : sqrt(delta)]
			fxch st(2)			; [sqrt(delta) : -b : -b]
								;
			fadd st(1), st		; [sqrt(delta) : -b+sqrt(delta) : -b]
			fsubp st(2), st		; [-b+sqrt(delta) : -b-sqrt(delta)]
								;
			fld1				; [1 : -b+sqrt(delta) : -b-sqrt(delta)]
			fld1				; [1 : 1 : -b+sqrt(delta) : -b-sqrt(delta)]
			fadd				; [2 : -b+sqrt(delta) : -b-sqrt(delta)]
			fmul a				; [2a : -b+sqrt(delta) : -b-sqrt(delta)]
			fdiv st(1), st		; [2a : -b+sqrt(delta)/2a : -b-sqrt(delta)]
			fdivp st(2), st		; [-b+sqrt(delta)/2a : -b-sqrt(delta)/2a]
			fstp qword ptr [r9 + 4 * 0 - 4]
			fstp qword ptr [r9 + 4 * 1 - 4]

			jmp Ender
		
		Equal:
			fld b				; [b : delta]
			fchs				; [-b : delta]
			fstp st(1)			; [-b]
			fld1				; [1 : -b]
			fld1				; [1 : 1 : -b]
			fadd				; [2 : -b]
			fmul a				; [2a : -b]
			fdivp st(1), st		; [-b/2a]
			fstp qword ptr [r9 + 4 * 0 - 4]
			fstp qword ptr [r9 + 4 * 1 - 4]

			jmp Ender
		Below:
			; Nie ma rzeczywistych miejsc zerowych
		Ender:
		
		movd xmm0, delta
        ret
QuadraticEquation64 ENDP

_TEXT ENDS
END