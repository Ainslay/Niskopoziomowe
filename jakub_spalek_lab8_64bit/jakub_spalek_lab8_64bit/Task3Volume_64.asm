_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC Task3Volume_64	;(float a, float b, float c)
Task3Volume_64 PROC , a:dword , b:dword , c:dword
	    
        movd a, xmm0;
        movd b, xmm1;
        movd c, xmm2;

        fld c               ; przeniesienie c na stos      [c]
        fld b               ; przeniesienie b na stos      [b : c]
        fmul a              ; st(0) = a * b                [a*b : c]
        fmulp st(1), st     ; st(1) = a*b * c              [a*b*c]

        fstp c              ; zapis do wyniku, c = st(0)   [stos pusty]
        
        movd xMM0, c

        ret
Task3Volume_64 ENDP

_TEXT ENDS
END