global _asm_inthandler21_keyboard

extern inthandler21_keyboard

[section .text]
[bits 32]
_asm_inthandler21_keyboard:	; IRQ 1		keyboard
		PUSH	ES			
		PUSH	DS
		PUSHAD					;save the register
		MOV		EAX,ESP
		PUSH	EAX
		MOV		AX,SS			;change DS ES SS
		MOV		DS,AX
		MOV		ES,AX
		CALL	inthandler21_keyboard	; call keyboard handler
		POP		EAX				;restore register
		POPAD
		POP		DS
		POP		ES
	
		IRETD					; return


