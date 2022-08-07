[GLOBAL read_hd0]
[GLOBAL read_hd1]
read_hd0:
mov ebx,[esp+4]
mov dx,0x1f6
mov al,0xa0
out dx,al

mov dx,0x1f7
mov al,0xec
out dx,al

not_ready2:
mov dx,0x1f7
in ax,dx
and al,0x08
cmp al,0x08
jnz not_ready2

mov esi,ebx  ;;储存的内存区域

mov cx,256
rrr:
mov dx,0x1f0
in ax,dx
mov [esi],ax
add esi,2
loop rrr

ret
.end

read_hd1:
mov ebx,[esp+4]
mov dx,0x3f6
mov al,0xa0
out dx,al

mov dx,0x3f7
mov al,0xec
out dx,al

not_ready2_2:
mov dx,0x3f7
in ax,dx
and al,0x08
cmp al,0x08
jnz not_ready2_2

mov esi,ebx  ;;储存的内存区域

mov cx,256
rrr_2:
mov dx,0x3f0
in ax,dx
mov [esi],ax
add esi,2
loop rrr_2

ret
.end