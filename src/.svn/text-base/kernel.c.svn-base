#include "../include/defs.h"
#include "../include/kasm.h"
#include "../include/cpu_info.h"
#include "../include/keyboard.h"
#include "../include/stdio.h"
#include "../include/shell.h"

void funcionPrincipal();
extern int cursor;

DESCR_INT idt[0x81];		/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

void int_20() 
{    
    return;
}


/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

kmain() 
{

	int i,num;


	//screen_cursor(0);
	screen_cursor(200);

/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */
	setup_IDT_entry (&idt[0x00], 0x08, (dword)&_int_00_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x01], 0x08, (dword)&_int_01_hand, ACS_EXC, 0);
    	setup_IDT_entry (&idt[0x02], 0x08, (dword)&_int_02_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x03], 0x08, (dword)&_int_03_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x04], 0x08, (dword)&_int_04_hand, ACS_EXC, 0);
    	setup_IDT_entry (&idt[0x05], 0x08, (dword)&_int_05_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x06], 0x08, (dword)&_int_06_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x07], 0x08, (dword)&_int_07_hand, ACS_EXC, 0);
    	setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_EXC, 0);
    	setup_IDT_entry (&idt[0x0A], 0x08, (dword)&_int_0A_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x0B], 0x08, (dword)&_int_0B_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x0C], 0x08, (dword)&_int_0C_hand, ACS_EXC, 0);
    	setup_IDT_entry (&idt[0x0D], 0x08, (dword)&_int_0D_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x0E], 0x08, (dword)&_int_0E_hand, ACS_EXC, 0);
    	setup_IDT_entry (&idt[0x0F], 0x08, (dword)&_int_0F_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x10], 0x08, (dword)&_int_10_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x11], 0x08, (dword)&_int_11_hand, ACS_EXC, 0);
    	setup_IDT_entry (&idt[0x12], 0x08, (dword)&_int_12_hand, ACS_EXC, 0);
	setup_IDT_entry (&idt[0x13], 0x08, (dword)&_int_13_hand, ACS_EXC, 0);



	setup_IDT_entry (&idt[0x20], 0x08, (dword)&_int_20_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x21], 0x08, (dword)&_int_21_hand, ACS_INT, 0);
    	setup_IDT_entry (&idt[0x80], 0x08, (dword)&_int_80_hand, ACS_INT, 0);
	
/* Carga de IDTR    */




	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

	_Cli();
	


/* Habilito interrupcion de timer tick*/
	
	_set_pic();
    	_mascaraPIC1(0xFC);
    /*          1111 1100   */
	_mascaraPIC2(0xFF);
    /*          1111 1111   */
        
	_Sti();
		
		
	/* Borra la pantalla. */
	k_clear_screen();
	
	inicializarPantalla();

	/*char *video = (char *) 0xb8000;
	video[0]='c';*/
	
	funcionPrincipal();
	
}


void screen_cursor(int cur){
	_outport(0x3D4, 14);
	_outport(0x3D5, cur);
	_outport(0x3D4, 15);
	_outport(0x3D5, cur);
}


