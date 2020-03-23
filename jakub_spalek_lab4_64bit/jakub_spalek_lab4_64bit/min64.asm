_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC Min64
	Min64 PROC		;(_int64 n, _int64 * tab) (rcx, rdx)
		
		push rcx
		push rdx

		mov rax, [rdx + 8 * rcx - 8]
		dec rcx

		Szukaj:
			cmp rax, [rdx + 8 * rcx - 8]
			cmovg rax, [rdx + 8 * rcx - 8]
			loop Szukaj
	
		pop rdx
		pop rcx

		ret

	Min64 ENDP
_TEXT ENDS
END