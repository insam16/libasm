section .text
global ft_strcmp

ft_strcmp:
	xor r8, r8
	.loop:
		mov r9, [rdi+r8]
		cmp r9, [rsi+r8]
		jne .calc
		cmp byte r9, 0
		je .calc
		inc r8
		jmp .loop
	.calc:
		mov rax, r9
		sub rax, [rsi+r8]
	ret
