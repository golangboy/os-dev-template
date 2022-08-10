org 0x7c00

;获取物理内存大小c 
	mov ebx,0
    mov edx,0
	mov di,_MemChkBuf ;请忽略es,假设已经正确设置好了
.loop:
	mov eax,0e820h
	mov ecx,20
	mov edx,0534D4150h ;'SMAP'
	int 15h

	jc LABEL_MEM_CHK_FAIL ;检查CF，是否发生错误
	add di,20	;由于执行INT 15h之后es和di不发生改变，就需要手动修改
	inc dword [_dwMCRNumber] ;记录ARDS的数量
	cmp ebx,0;判断是否到达最后一个内存区域

	jne .loop
	jmp LABEL_MEM_CHK_OK ;ebx=0到达最后一个内存区域
LABEL_MEM_CHK_FAIL:
	mov dword [_dwMCRNumber],0
LABEL_MEM_CHK_OK:
;Read kernel from hd
; 扇区数
mov ax,0x1f2
mov dx,ax
mov ax,0xff
out dx,al

;0-7
mov ax,0x1f3
mov dx,ax
mov ax,0
out dx,al

;8-15
mov ax,0x1f4
mov dx,ax
mov ax,0
out dx,al

;16-23
mov ax,0x1f5
mov dx,ax
mov ax,0
out dx,al

;24-27
mov ax,0x1f6
mov dx,ax
mov ax,0xe0
out dx,al

;请求读
mov ax,0x1f7
mov dx,ax
mov ax,0x20
out dx,al


not_ready:
;检测状态
in al,dx
and al,0x08
cmp al,0x08
jnz not_ready


;读取次数
mov cx,65280

;写入的位置
mov bx,0x8000

read:
;开始读取数据
mov ax,0x1f0
mov dx,ax
in ax,dx
mov [bx],ax
add bx,2
loop read


in al,0x92
or al,2
out 0x92,al

mov eax,cr0
or eax,1
mov cr0,eax

mov eax,0x8000
add eax,0x18
mov ebx,[eax]

lgdt [gdt_ptr]
jmp 8:flush_cs

[bits 32]
flush_cs:
mov ax,0x10
mov ds,ax
mov es,ax
mov ss,ax
mov fs,ax
mov gs,ax
push dword _MemChkBuf
push dword _dwMCRNumber
call ebx

gdt_ptr:
dw 23
dd gdt_table_base
;;GDT
gdt_table_base:
dq 0
dq 0xCF9A000000FFFF
dq 0xCF92000000FFFF

_dwMCRNumber: dw 0   ;记录ARDS的数量
_MemChkBuf: times 256 db 0
times 510-($-$$) db 0
db 0x55
db 0xaa