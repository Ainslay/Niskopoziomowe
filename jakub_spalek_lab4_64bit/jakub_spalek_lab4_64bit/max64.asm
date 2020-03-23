_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC Max64
	Max64 PROC		;(_int64 n, _int64 * tab) (rcx, rdx)
		
		push rcx
		push rdx

		mov rax, [rdx + 8 * rcx - 8]
		dec rcx

		Szukaj:
			cmp rax, [rdx + 8 * rcx - 8]
			cmovl rax, [rdx + 8 * rcx - 8]
			loop Szukaj
	
		pop rdx
		pop rcx

		ret

	Max64 ENDP
_TEXT ENDS
END