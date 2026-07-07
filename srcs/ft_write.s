section .text
global ft_write

ft_write:
    mov rax, 1
    syscall

    cmp rax, 0
    jl .err
    .end:
    ret
    .err:
    ; errno = -rax
    ; rax = -1
    jmp .end
    