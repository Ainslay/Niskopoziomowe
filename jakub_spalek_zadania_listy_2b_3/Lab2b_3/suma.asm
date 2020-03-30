_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

	hello_msg db "Hello world!", 0			;dekl. danych – zestawu bajtów
	info_msg db "Info", 0					;³añcuchy znaków zakoñcz zerem
	EXTERN MessageBoxA: PROC				;dekl. zewnêtrznej funkcji
	EXTERN GetForegroundWindow: PROC
	
	PUBLIC hello_world_asm
	hello_world_asm PROC					;deklaracja podprogramu
		push rbp							;zabezpiecz rej. rbp wskaŸnik ramy
		mov rbp, rsp						;ustaw nowy wskaŸnik ramy stosu
		sub rsp, 8 * (4 + 2)				;alokacja miejsca dla parametrów
											;wywo³ania (co najmniej 4)
											;+ 2 QWORD dla wyrównania stosu
		and rsp, not 15						;wyrównanie stosu do 16 bajtów przed
											;wywo³aniem funkcji API
		call GetForegroundWindow			;Pobierz uchwyt okna
		mov rcx, rax
											;Sposób wywo³ania funkcji MessageBoxA:
											; WINUSERAPI int WINAPI MessageBoxA(
											; RCX => _In_opt_ HWND hWnd,
											; RDX => _In_opt_ LPCSTR lpText,
											; R8 => _In_opt_ LPCSTR lpCaption,
											; R9 => _In_ UINT uType);
		mov rdx, offset hello_msg
		mov r8, offset info_msg

		mov r9, 1 ;

		; dla 0 : wyswietla sie przycisk ok
		; dla 1 : wyswietla sie przycisk ok, anuluj
		; dla 2 : wyswietla sie przycisk przerwij, ponow_probe, anuluj
		; dla 3 : wyswietla sie przycisk tak, nie, anuluj
		; dla 4 : wyswietla sie przycisk tak, nie
		; dla 5 : wyswietla sie przycisk ponow_probe, anuluj
		; dla 6 : wyswietla sie przycisk anuluj, ponow_probe, kontynuuj
		; dla 7 : nie wyswietla sie zadne okno

		call MessageBoxA
		mov rsp, rbp						;przywrócenie wskaŸnika stosu
		pop rbp								;przywrócenie wskaŸnika ramy stosu
		ret									;powrót z podprogramu
	
	hello_world_asm ENDP

_TEXT ENDS
END