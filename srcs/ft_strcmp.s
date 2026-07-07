section .text
global ft_strcmp

ft_strcmp:
	xor r8, r8
	.loop:
		movzx r9, byte [rdi+r8]
		movzx r10, byte [rsi+r8]
		cmp r9, r10
		jne .calc
		test r9, r9
		je .calc
		inc r8
		jmp .loop
	.calc:
		mov rax, r9
		sub rax, r10
	ret

section .note.GNU-stack noalloc noexec
