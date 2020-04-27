_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC Task3SideSurfaceArea_64	;(float a, float b, float c)
Task3SideSurfaceArea_64 PROC , a:dword , b:dword , c:dword
	    
        movd a, xmm0;
        movd b, xmm1;
        movd c, xmm2;

        fld c               ; przeniesienie c na stos      [c]
        fld st              ; powielenie c                 [c : c]
        fld1                ; przeniesienie 1 na stos      [1 : c : c]
        fld st              ; powielenie 1                 [1 : 1 : c : c]
        faddp st(1), st     ; st(1) = 1 + 1                [2 : c : c]
        fld st              ; powielenie 2                 [2 : 2 : c : c]
        fld a               ; przeniesienie a na stos      [a : 2 : 2 : c : c]
                            
        fmulp st(1), st     ; st(1) = 2 * a                [2a : 2 : c : c]
        fmulp st(3), st     ; st(3) = 2a * c               [2 : c : 2ac]
        fld b               ; przeniesienie b na stos      [b : 2 : c : 2ac]
        fmulp st(1), st     ; st(1) = 2 * b                [2b : c: 2ac]
        fmulp st(1), st     ; st(1) = 2b * c               [2bc : 2ac]
        faddp st(1), st     ; st(1) = 2ac + 2bc            [2ac+2bc]

        fstp c              ; zapis do wyniku, c = st(0)   [stos pusty]
        
        movd xMM0, c

        ret
Task3SideSurfaceArea_64 ENDP

_TEXT ENDS
END