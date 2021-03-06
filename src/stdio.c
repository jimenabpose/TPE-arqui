#include "../include/defs.h"
#include "../include/video.h"
#include "../include/stdio.h"
#include "../include/kasm.h"

#define	TOPE_FILAS	40
#define	TOPE_COLS	80


byte videoBuffer[V_BUFFER_LENGTH] = {0};
byte cleanBuffer[4000] = {0};
byte screenBuffer[4160] = {};
byte blankScreenBuffer[4000] = {' ', 0x09, ' ', 0x09, ' ', 0x09};
static int vb_counter = 0;

extern teclator tecl;

int cursor = 0;
int tickpos = 0;

/*
* Funciones de la int 80h
*/
byte int_80(dword op, dword data, dword offset, dword fd)
{
	if(op == WRITE)
	{
		if (fd == FD_PANTALLA)
		{
			write_screen(data,offset);
			cursor = cursor + 2;
			return 0;
		}
	}
	else if(op == READ)
	{
		if (fd == FD_TECLADO)
		{
			return next_char();
		}
	}
}

void write(int fd, const void* buffer, int count) {
	int i;
	int offset;
	byte data;

	for ( i = 0 ; i<count; i++) {
		offset = i + cursor;
		data = *((byte *)buffer+i);
		screenBuffer[offset] = data;
		_call_int_80(WRITE, fd, offset, data);
	}

	/*cursor+=count/2;*/

}

byte read(int fd, void* buffer, int count) {
	int i;
	byte * b = (byte *)buffer;
    	for ( i = 0 ; i<count; i++) {
        	b[i] = _call_int_80(READ, fd, i, 0);
        	if (b[i] == 0xFF) { 
            		break;
        	}
    	}
    
	return i;
}

/*
* flush
*
* si queda algo en el buffer de put_char, lo imprime
* 
*/
void flush() {
	write(FD_PANTALLA,tecl.buf,tecl.size);
    /*if (cursor + vb_counter >= 4000) {
        check_screen_scroll(vb_counter);
        write(FD_PANTALLA, videoBuffer, vb_counter);
        vb_counter = 0;
    } else {
        write(FD_PANTALLA, videoBuffer, vb_counter);
        vb_counter = 0;
    }*/
}

/*
* se fija si hay q scrollear la pantalla
* 
*/

void check_screen_scroll(int offset) {
    if (cursor + offset >= 4000) {
        page_roll(4000-cursor);
    }
    return;
}

/* 
* scrolea la pantalla para arriba 
*/

void page_roll(int backwards) {
	int i;
	cursor = 0;
	for(i=0;i<4000;i=i+2){
		write(FD_PANTALLA, screenBuffer+160+i,1);
	}	
  	cursor = 4000-160;
    return;
}

/* 
* Funcion printf de C, imprime en pantalla los argumentos que se le pasan
*/

void
printf ( const char *format, ... )
{
	char **arg = (char **) &format;
	int c;
	char buf[20];
	
	_Cli();
	
	arg++;

	while ((c = *format++) != 0)
	{
		if (c != '%')
		{
			printChar(c);
		}
		else
		{
			char *p;
			c = *format++;

			switch (c)
			{
				case 'd':
				case 'u':
				case 'x':
					itoa (buf, c, *((int *) arg++));
					p = buf;
					goto string;
					break;

				case 's':
					p = *arg++;
					if (! p)
						p = "(null)";

				string:
					while (*p)
					printChar (*p++);
					break;

				default:
					printChar (*((int *) arg++));
					break;
			}
		}	
	}
	_Sti();
}

/*
* Imprime en pantalla el char que se le pasa
*/
void
printChar( unsigned char ascii )
{

	_Cli();

	check_screen_scroll(0);
	
	/* Si es el backspace */
	if(ascii == '\x08')
	{
		cursor -= 2;
        write(FD_PANTALLA, cleanBuffer, 1);
        cursor -=2;
	}
	/* Si es un tab */
	else if(ascii == '\t')
	{
		print_tab();
	}
	else
	{
		write(FD_PANTALLA, &ascii, 1);
	}
	
	_Sti();

	return;

}

void
print_new_line()
{	
	cursor = (cursor + 160 - (cursor % 160));
	printf("Johnelite> ");
}

void
print_enter()
{
	cursor = (cursor + 160 - (cursor % 160));
}

void
print_tab()
{
	cursor = (cursor + 20 - (cursor % 20));
}


void
erase_a_character()
{
	char esp= ' ';
    cursor -= 2;
    write(FD_PANTALLA, &esp, 1);
    cursor -= 2;
}

void
garbage()
{
	char c = 'a';
        int i;
        for (i = 0; i<2000; i++)
        {
		printChar(c++%50+'a');
		flush();
	}
}

#define K_BUFFER_LENGTH 1

byte keyboard_buffer[K_BUFFER_LENGTH] = {0};
int kb_counter = K_BUFFER_LENGTH;
int n_read = K_BUFFER_LENGTH;

byte get_char() {
	read(FD_TECLADO, keyboard_buffer, 1);
	return keyboard_buffer[0];    
    if ( kb_counter == n_read ) {
	do 
        {
		    n_read = read(FD_TECLADO, keyboard_buffer, K_BUFFER_LENGTH);
       }
        while (n_read == 0);
		    kb_counter = 0;
    }
    return keyboard_buffer[kb_counter++];
}


/*************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen()
{
	int i = 0;
	cursor = 0;
	while(i < 80*25){
		write(FD_PANTALLA,cleanBuffer,1);
		i++;
	}
	
	cursor = 0;
}
