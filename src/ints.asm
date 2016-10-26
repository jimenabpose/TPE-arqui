GLOBAL _int_00_hand
GLOBAL _int_01_hand
GLOBAL _int_02_hand
GLOBAL _int_03_hand
GLOBAL _int_04_hand
GLOBAL _int_05_hand
GLOBAL _int_06_hand
GLOBAL _int_07_hand
GLOBAL _int_08_hand
GLOBAL _int_09_hand
GLOBAL _int_0A_hand
GLOBAL _int_0B_hand
GLOBAL _int_0C_hand
GLOBAL _int_0D_hand
GLOBAL _int_0E_hand
GLOBAL _int_0F_hand
GLOBAL _int_10_hand
GLOBAL _int_11_hand
GLOBAL _int_12_hand
GLOBAL _int_13_hand
GLOBAL _int_20_hand
GLOBAL _int_21_hand



; Extern functions declarations.

EXTERN int_00
EXTERN int_01
EXTERN int_02
EXTERN int_03
EXTERN int_04
EXTERN int_05
EXTERN int_06
EXTERN int_07
EXTERN int_08
EXTERN int_09
EXTERN int_0A
EXTERN int_0B
EXTERN int_0C
EXTERN int_0D
EXTERN int_0E
EXTERN int_0F
EXTERN int_10
EXTERN int_11
EXTERN int_12
EXTERN int_13
EXTERN int_20
EXTERN int_21




_int_00_hand:
	push	ebp
	mov	ebp,esp

	call	int_00
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_01_hand:
	push	ebp
	mov	ebp,esp

	call	int_01
	
	mov	esp,ebp
	pop	ebp
   	
	iret

_int_02_hand:

	push	ebp
	mov	ebp,esp

	call	int_02
	
	mov	esp,ebp
	pop	ebp
   	
	iret

_int_03_hand:

	push	ebp
	mov	ebp,esp

	call	int_03
	
	mov	esp,ebp
	pop	ebp
   	
	iret

_int_04_hand:

	push	ebp
	mov	ebp,esp

	call	int_04
	
	mov	esp,ebp
	pop	ebp
   	
	iret



_int_05_hand:

	push	ebp
	mov	ebp,esp

	call	int_05
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_06_hand:

	push	ebp
	mov	ebp,esp

	call	int_06
	
	mov	esp,ebp
	pop	ebp
   	
	iret

_int_07_hand:

	push	ebp
	mov	ebp,esp

	call	int_07
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_08_hand:

	push	ebp
	mov	ebp,esp

	call	int_08
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_09_hand:

	push	ebp
	mov	ebp,esp

	call	int_09
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_0A_hand:

	push	ebp
	mov	ebp,esp

	call	int_0A
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_0B_hand:

	push	ebp
	mov	ebp,esp

	call	int_0B
	
	mov	esp,ebp
	pop	ebp
   	
	iret

_int_0C_hand:

	push	ebp
	mov	ebp,esp

	call	int_0C
	
	mov	esp,ebp
	pop	ebp
   	
	iret



_int_0D_hand:

	push	ebp
	mov	ebp,esp

	call	int_0D
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_0E_hand:

	push	ebp
	mov	ebp,esp

	call	int_0E
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_0F_hand:

	push	ebp
	mov	ebp,esp

	call	int_0F
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_10_hand:

	push	ebp
	mov	ebp,esp

	call	int_10
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_11_hand:

	push	ebp
	mov	ebp,esp

	call	int_11
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_12_hand:

	push	ebp
	mov	ebp,esp

	call	int_12
	
	mov	esp,ebp
	pop	ebp
   	
	iret


_int_13_hand:

	push	ebp
	mov	ebp,esp

	call	int_13
	
	mov	esp,ebp
	pop	ebp
   	
	iret

