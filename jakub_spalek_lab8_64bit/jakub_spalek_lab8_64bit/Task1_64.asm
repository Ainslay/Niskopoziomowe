_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC Task1_64		;(float a, float b, float c, float d, float x)
Task1_64 PROC , a:dword , b:dword , c:dword, d:dword, x:dword
	    
        movd a, xmm0;
        movd b, xmm1;
        movd c, xmm2;
        movd d, xmm3;					 

        fld d               ; przeniesienie d na stos                  [d]
        fld x               ; przeniesienie x na stos                  [x : d]
        fld st              ; powielenie x                             [x : x : d]
        fmul st, st(1)      ; st(0) = st(0) * st(1) = x * x            [xx : x : d]
                            
        fld st(1)           ; przeniesienie na stos st(1) = x          [x : xx : x : d]
        fmul st, st(1)      ; st(0) = x * xx                           [xxx : xx : x : d]
        fmul a              ; st(0) = xxx * a                          [axxx : xx : x : d]
                            
        faddp st(3), st     ; st(3) = d + axxx, st(0) zdjête ze stosu  [xx : x : axxx+d]
        fmul b              ; st(0) = xx * b                           [xxb : x : axxx+d]
        faddp st(2), st     ; st(2) = axxx+d + bxx, st(0) zdjête       [x : axxx+bxx+d]
        fmul c              ; st(0) = x * c                            [cx : axxx+bxx+d]
        faddp st(1), st     ; st(1) = axxx+bxx+d + xc, st(0) zdjête    [axxx+bxx+xc+d]
                            
        fstp x              ; zapis do wyniku, x= st(0), st(0) zdjête  [stos pusty]
        
        movd xMM0, x

        ret
Task1_64 ENDP

_TEXT ENDS
END