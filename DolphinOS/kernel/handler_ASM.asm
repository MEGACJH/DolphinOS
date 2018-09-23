global _asm_inthandler21_keyboard

extern inthandler21_keyboard

INT_M_CTL EQU 0X20
EOI EQU 0X20

[section .text]
[bits 32]
_asm_inthandler21_keyboard:	; IRQ 1		keyboard
	PUSH	ES			
	PUSH	DS
	PUSHAD					
	MOV		EAX,ESP
	PUSH	EAX
	MOV		AX,SS			
	MOV		DS,AX
	MOV		ES,AX
	CALL	inthandler21_keyboard	
	POP		EAX				
	POPAD
	POP		DS
	POP		ES
	IRETD					
	
