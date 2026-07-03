section .text
global ft_strcpy

ft_strcpy:
	xor rax, rax
	.loop:
		mov cl, [rsi+rax]
		mov [rdi+rax], cl
		cmp byte [rsi+rax], 0
		je .break
		inc rax
		jmp .loop
	.break:
	mov rax, rdi
	ret
