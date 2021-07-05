[SECTION .text class=CODE USE32]
[BITS 32]

global _add2, add2

_add2:
add2:
	push ebp
	mov ebp, esp

	mov eax, [ebp+8]
	add eax, [ebp+12]

	mov esp, ebp
	pop ebp
	retn
