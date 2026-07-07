section .text
global ft_write
extern __errno_location

ft_write:
    mov rax, 1
    syscall

    cmp rax, 0
    jl .err
    .end:
    ret

.err:
    neg rax
    push rax
    call __errno_location wrt ..plt
    pop qword [rax]
    mov rax, -1
    jmp .end

section .note.GNU-stack noalloc noexec
