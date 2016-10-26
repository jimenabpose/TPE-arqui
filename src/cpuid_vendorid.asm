
section .bss ; $Revision: 1.6 $
vendor_id       resd	12	;reserve 12 bytes of memory


section .text
    global _vendor_id                       ;must be declared for linker (ld)


_vendor_id:					;tell linker entry point

	mov eax,0
	cpuid
	mov [vendor_id],ebx
	mov [vendor_id+4],edx
	mov [vendor_id+8],ecx

        push    ebp
        mov     ebp,esp            ; genera stack frame

	mov eax,vendor_id
	        
	mov     esp,ebp
        pop     ebp
        ret

