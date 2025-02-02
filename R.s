section .data
    FPS dd 60.0    ; Define FPS as a 32-bit float

section .text
    global R
    R:              ; Regular (rdi -> velocity)
        push rbp
        mov rbp, rsp
        
        ; Convert integer velocity to float
        cvtsi2ss xmm0, rdi     ; Convert velocity (in rdi) to float in xmm0
        
        ; Load FPS value and divide
        movss xmm1, [FPS]      ; Load FPS into xmm1
        divss xmm0, xmm1       ; Divide velocity by FPS
        
        ; Return value is already in xmm0 for float return
        
        leave
        ret

section	.note.GNU-stack