
section .bss ; $Revision: 1.6 $
brand      resd	16	;reserve 12 bytes of memory


section .text
    global _brand_string                       ;must be declared for linker (ld)


_brand_string:					;tell linker entry point

        push    ebp
        mov     ebp,esp            ; genera stack frame

	mov eax,[ebp+8]
	cpuid
	mov [brand],eax
	mov [brand+4],ebx
	mov [brand+8],ecx
	mov [brand+12],edx

	mov eax,brand
	        
	mov     esp,ebp
        pop     ebp
        ret

