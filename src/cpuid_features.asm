section .bss ; $Revision: 1.6 $
features	resd	4

section .text
    	global _edx_features                       ;must be declared for linker (ld)
	global _ecx_features

_edx_features:					;tell linker entry point

        push    ebp
        mov     ebp,esp            ; genera stack frame

	mov eax,1
	cpuid
	
	mov [features],edx

	mov eax,[features]       	

        mov     esp,ebp
        pop     ebp
 
	ret

_ecx_features:

	push    ebp
        mov     ebp,esp            ; genera stack frame

	mov eax,1
	cpuid
	
	mov [features],ecx

	mov eax,[features]       	

        mov     esp,ebp
        pop     ebp
 
	ret
