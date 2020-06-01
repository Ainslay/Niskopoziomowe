_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC Koprocesor	;(double a, double b, double c, double x) xmm0, xmm1, xmm2, xmm3
Koprocesor PROC	, a:qword , b:qword , c:qword, x:qword

	; Rownanie: 2x^2 - ax^2 * (b-c)
	; ONP: x x * 2 * x x * a * b c - * -

	movq a, xmm0
	movq b, xmm1
	movq c, xmm2
	movq x, xmm3

	fld1							; [1]
	fld st							; [1 : 1]
	faddp							; [2]
	fld x							; [x : 2]
	fld st							; [x : x : 2]
	fmul x							; [x^2 : x : 2]
	fmulp st(2), st					; [x : 2x^2]

	fmul x							; [x^2 : 2x^2]
	fmul a							; [ax^2 : 2x^2]

	fld b							; [b : ax^2 : 2x^2]
	fsub c							; [b-c : ax^2 : 2x^2]
	fmulp							; [ax^2*(b-c) : 2x^2]
	fsubp							; [2x^2 - ax^2*(b-c)]

	fstp a;							; zapis wyniku
	movq xmm0, a

	ret
Koprocesor ENDP
_TEXT ENDS
END