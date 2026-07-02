section .text
global ft_strlen

ft_strlen:
	xor rax, rax
	.loop:
		cmp byte [rdi+rax], 0
		je .break
		inc rax
		jmp .loop
	.break:
	ret
