_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC ZerujTablice64
	ZerujTablice64 PROC		;(_int64 n, _int64 * tab) (rcx, rdx)
		
		push rcx
		push rdx

		xor rax, rax

		Zeruj:
			mov [rdx + 8 * rcx - 8], rax
			loop Zeruj
	
		pop rdx
		pop rcx

		ret
	ZerujTablice64 ENDP
_TEXT ENDS
END