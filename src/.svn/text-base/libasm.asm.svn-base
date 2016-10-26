GLOBAL  _read_msw,_lidt
GLOBAL  _int_20_hand
GLOBAL  _int_21_hand
GLOBAL	_int_80_hand
GLOBAL 	_call_int_80
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL 	 _set_pic
GLOBAL  _debug
GLOBAL	_pruebaSuma
GLOBAL	_wscreen
GLOBAL	_outport
GLOBAL _general_protection

EXTERN  int_20
EXTERN  int_21
EXTERN	int_80


SECTION .text

_outport:
	push 	ebp
	mov		ebp, esp
	mov 	dx, [ss:ebp+8]
	mov 	al, [ss:ebp+12]
	out 	dx, al
	mov 	esp, ebp
	pop 	ebp
	ret

_Cli:
	cli			; limpia flag de interrupciones
	ret

_Sti:

	sti			; habilita interrupciones por flag
	ret

_mascaraPIC1:			; Escribe mascara del PIC 1
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	21h,al
        pop     ebp
        retn

_mascaraPIC2:			; Escribe mascara del PIC 2
	push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out	0A1h,al
        pop     ebp
        retn

_read_msw:
        smsw    ax		; Obtiene la Machine Status Word
        retn


_lidt:				; Carga el IDTR
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR 
	rol	ebx,16		    	
	lidt    [ds: ebx]          ; carga IDTR
        pop     ebx
        pop     ebp
        retn


_int_20_hand:				; Handler de INT 8 ( Timer tick)
        push    ds
        push    es                      ; Se salvan los registros
        pusha                           ; Carga de DS y ES con el valor del selector
        mov     ax, 10h			; a utilizar.
        mov     ds, ax
        mov     es, ax                  
        call    int_20                 
        mov		al,20h			; Envio de EOI generico al PIC
		out		20h,al
		popa                            
        pop     es
        pop     ds
        iret
        
_int_21_hand:				; Handler de INT 09 ( Keyboard)
		push	ebp
		mov		ebp,esp
		pusha

								; llamo a la int 80 con los parametros
		mov		eax,00h
		in		al,60h			; leo del puerto 60h
		mov		ah,00h
		
		push eax

		call	int_21

		pop eax

		add		esp,4
	
		mov		al,20h			; Envio de EOI generico al PIC
		out		20h,al

		popa
		mov		esp,ebp
		pop	ebp
		iret

_call_int_80:
		push	ebp
		mov	ebp,esp
		push	ebx
		push	ecx
		push	edx
	
		mov	eax,0
		mov	ebx,0
		mov	edx,0
	
		mov	ax,[ebp+8]		; op
		mov	bx,[ebp+12]		; fd
		mov	ecx,[ebp+16]	; offset
		mov	dx,[ebp+20]		; data
		
		
		int 80h
		
		pop	edx
		pop	ecx
		pop	ebx
		mov	esp,ebp
		pop	ebp
		ret
		
_int_80_hand:
		push	ebp
		mov		ebp,esp
		pusha

		push	ebx		; fd
		push	ecx		; offset
		push	edx		; data
		push	eax		; op
		
		call	int_80
		
		pop		eax
		pop		edx
		pop		ecx
		pop		ebx
	
		popa
		mov		esp,ebp
		pop		ebp
		ret
		
_wscreen:
		push	ebp
		mov	ebp,esp
		pusha
		
		mov	dl,[ebp+8]
		mov	ecx,[ebp+12]
	
		mov	ax,10h			
		mov	ds,ax
		
		mov	ebx,0B8000h			; Escribo en la pantalla
		add	ebx,ecx
	
		mov	[ds:ebx],dl
		
		popa
		mov	esp,ebp
		pop	ebp
   		ret
   		
_set_pic:

;seteo pic1
                          
	mov     al,11h		;inicializa el pic	       	
	out     20h,al     	;mando 11h a la zona de comandos
	mov     al,20h		;vector de interrupciones del pic1 empieza en 
						;20h para no pisar las excepciones            
	out     21h,al     	;mando 20h a la zona de datos
	mov     al,4h		;cargo 4h para q el slave este colgado de la irq2          
	out     21h,al         	
	mov     al,1h 		;modo 8086/8088
	out 	21h,al		

;seteo pic2

 	mov     al,11h      
	out     0A0h,al         
	mov     al,28h      ;vector de interrupciones del pic2 en 20h+8h   
	out     0A1h,al         
	mov     al,2h       ;slave va conectado al irq2
	out     0A1h,al         
	mov     al,1h            
	out     0A1h,al
     
	retn	

_general_protection:
	mov eax,0
	push eax
	iret



; Debug para el BOCHS, detiene la ejecucion 
;Para continuar colocar en el BOCHSDBG: set $eax=0

_debug:
        push    bp
        mov     bp, sp
        push	ax
vuelve:	mov     ax, 1
        cmp	ax, 0
	jne	vuelve
	pop	ax
	pop     bp
        retn
