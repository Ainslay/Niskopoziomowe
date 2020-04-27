_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC Task2_64		;(float a, float b, float c, float x)
Task2_64 PROC , a:dword , b:dword , c:dword, x:dword
	    
        movd a, xmm0;
        movd b, xmm1;
        movd c, xmm2;
        movd x, xmm3;					 

        fld a               ; przeniesnie a na stos                [a]
        fld1                ; przeniesnie 1 na stos                [1 : a]
        fsubp st(1), st     ; st(1) = a - 1                        [a-1]
        fld st              ; powielenie (a-1)                     [a-1 : a-1]
        fmul st(1), st      ; st(1) = (a-1)*(a-1)                  [a-1 : (a-1)*(a-1)]
        fmulp st(1), st     ; st(1) = (a-1)^3                      [(a-1)^3]
        fmul x              ; st(0) = (a-1)^3 * x                  [(a-1)^3*x]
                            
        fld b               ; przeniesienie b na stos              [b : (a-1)^3*x]
        fld a               ; przeniesienie a na stos              [a : b : (a-1)^3*x]
        fsubp st(1), st     ; st(1) = b - a                        [b-a : (a-1)^3*x]
        fmul c              ; st(0) = (b-a) * c                    [(b-a)*c : (a-1)^3*x]
        faddp st(1), st     ; st(1) = (a-1)^3 + (b-a)*c            [(a-1)^3*x+(b-a)*c]
                            
        fld c               ; przeniesienie c na stos              [c : (a-1)^3*x+(b-a)*c]
        fld b               ; przeniesienie b na stos              [b : c : (a-1)^3*x+(b-a)*c]
        fsubp st(1), st     ; st(1) = c - b                        [c-b : (a-1)^3*x+(b-a)*c]
        fmul a              ; st(0) = (c-b) * a                    [(c-b)*a : (a-1)^3*x+(b-a)*c]
        faddp st(1), st     ; st(1) = (a-1)^3*x+(b-a)*c + (c-b)*a  [(a-1)^3*x+(b-a)*c+(c-b)*a]
                            
        fstp x              ; zapis do wyniku, x = st(0)           [stos pusty]
        
        movd xMM0, x

        ret
Task2_64 ENDP

_TEXT ENDS
END