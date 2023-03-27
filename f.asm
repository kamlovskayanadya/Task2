section .data

    const11 dd 1.5
    const12 dd 3.0
    const13 dd 1.0
    const21 dd 2.5
    const22 dd 9.5
    const31 dd 5.0


section .text
global f1

f1:    ; 1.5/(x+1) +3             
push ebp
mov ebp, esp

finit
fld dword[ebp + 8]
fld dword[const13]
fadd
xor edx, edx
fld dword[const11]  ;1.5
fld dword[ebp + 8]
fdiv
fld dword[const12]  ;3
faddp
mov esp, ebp
pop ebp
ret

global f2

f2:    ;2.5x-9.5
push ebp
mov ebp, esp

finit
fld dword[const21]  ;2.5
fld dword[ebp + 8]
fmul
fld dword[const22]  ;9.5
fsubp

mov esp, ebp
pop ebp
ret

global f3

f3:    ;5/x
push ebp
mov ebp, esp
finit
fld dword[const31]
fld dword[ebp + 8]
fdivp
mov esp, ebp
pop ebp
ret