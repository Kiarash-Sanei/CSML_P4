section .data
    FPS dd 60.0    ; Define FPS as a 32-bit float with exact value

section .text
    global R
    R:
        push rbp
        mov rbp, rsp
        
        ; Convert to double precision
        cvtsi2sd xmm0, rdi     ; Convert velocity to double
        cvtss2sd xmm1, [FPS]   ; Convert FPS to double
        
        ; Perform division in double precision
        divsd xmm0, xmm1       ; Divide with double precision
        
        ; Convert back to single precision for return
        cvtsd2ss xmm0, xmm0    ; Convert result back to float
        
        leave
        ret

section	.note.GNU-stack