section .text
global ft_read
extern __errno_location

ft_read:
    mov rax, 0
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
