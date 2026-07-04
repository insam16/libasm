section .text
global ft_strcpy

ft_strcpy:
	xor rax, rax
	.loop:
		mov cl, [rsi+rax]
		mov [rdi+rax], cl
		test cl, cl
		je .break
		inc rax
		jmp .loop
	.break:
	mov rax, rdi
	ret
