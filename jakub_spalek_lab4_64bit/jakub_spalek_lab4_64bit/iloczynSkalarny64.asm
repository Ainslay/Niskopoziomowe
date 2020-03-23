_DATA SEGMENT
_DATA ENDS
_TEXT SEGMENT

PUBLIC IloczynSkalarny64
	IloczynSkalarny64 PROC		;(_int64 * tab1, _int64 * tab2, _int64 n) (rcx, rdx, rax)
		
		push rsi
		push rdi

		xor rbx, rbx
		mov rsi, rcx
		mov rdi, rdx
		mov rcx, r8

		Suma:
			mov  rax, [rsi + 8 * rcx - 8]
            mul  qword ptr [rdi + 8 * rcx - 8] 
            add  rbx, rax                       
            loop Suma              
	
		mov rax, rbx

		pop rdi
		pop rsi

		ret

	IloczynSkalarny64 ENDP
_TEXT ENDS
END