_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC SumujElementyTablicy64
	SumujElementyTablicy64 PROC		;(_int64 n, _int64 * tab) (rcx, rdx)
		
		push rcx
		push rdx

		xor rax, rax

		Suma:
			add rax, [rdx + 8 * rcx - 8]
			loop Suma
	
		pop rdx
		pop rcx

		ret 
		
	SumujElementyTablicy64 ENDP
_TEXT ENDS
END