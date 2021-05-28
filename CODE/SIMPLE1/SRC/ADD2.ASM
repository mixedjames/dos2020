bits 16
cpu 8086

global _add2

segment _text class=code use16

_add2:
	push bp
	mov bp, sp

	mov ax, [bp+4]
	add ax, [bp+6]

	pop bp
	retn