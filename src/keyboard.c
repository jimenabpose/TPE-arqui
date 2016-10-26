#include "../include/defs.h"
#include "../include/cpu_info.h"
#include "../include/stdio.h"
#include "../include/shell.h"
#include "../include/keyboard.h"

#define NADA 0xFF
#define ESCAPE -2
#define MAX_CODES 150
#define TRUE	1
#define FALSE	0
#define AUX 0
#define ENG 0
#define SP 1

#define LONG_STR_TKN 100
#define LONG_STR_CMD 320

static int shift = 1;

static int idioma_teclado = ENG;

static char block_may = 1;

static char acento_esp = 0;

static char acento_eng = 0;

teclator tecl = {{0},0,0,0};

int bflag=FALSE;

/*Mapa de caracteres del teclado en inglés.*/

unsigned char ScanCodesEn[MAX_CODES][2] =	{ 				
	
	{NADA,NADA},
	/*Escape*/	{ESCAPE,ESCAPE},

	{'!','1'},{'@','2'},{'#','3'},{'$','4'},{'%','5'},
	{'^','6'},{'&','7'},{'*','8'},{'(','9'}, {')','0'},{'_','-'},{'+','='},
	
	/*BACKSPACE*/	{'\b','\b'}, 
	/*TAB*/	{'\t','\t'},

	{'Q','q'},{'W','w'},{'E','e'},{'R','r'},{'T','t'},{'Y','y'},{'U','u'},
	{'I','i'},{'O','o'},{'P','p'},{'{','['},{'}',']'},

	/*Enter*/	{'\n','\n'},
	/*CTRL IZQ*/	{NADA,NADA},

	{'A','a'},{'S','s'},{'D','d'},{'F','f'},{'G','g'},{'H','h'},{'J','j'},
	{'K','k'},{'L','l'},{':',';'}, {'"','\''},{'~','`'},

	{NADA,NADA},{'|','\\'},{'Z','z'},{'X','x'},{'C','c'},{'V','v'},{'B','b'},
	{'N','n'},{'M','m'},{'<',','},{'>','.'},{'?','/'},
	
	/*Shift Derecho*/	{NADA,NADA},{'*','*'},
	/*ALT IZQ*/	{NADA,NADA},
	/*Espacio*/	{' ',' '},
	/*CAPSLOCK*/	{NADA,NADA},

	/*F1*/	{NADA,NADA},{NADA,NADA},{NADA,NADA},{NADA,NADA},{NADA,NADA},
		{NADA,NADA},{NADA,NADA},{NADA,NADA},{NADA,NADA},{NADA,NADA},

	/*NUM LOCK*/	{NADA,NADA},
	/*SCROLL LOCK*/	{NADA,NADA},
					
	/*Key Pad*/

	{'7','7'},{'8','8'},{'9','9'},{'-','-'},
	{'4','4'},{'5','5'},{'6','6'},{'+','+'},
	{'1','1'},{'2','2'},{'3','3'},{'0','0'},
	{'.','.'},{NADA,NADA},{'+','*'},{'+','*'},
				
	/*F11*/{NADA,NADA},
	{NADA,NADA},//088 F12
	{'+','*'},	//089
	{'+','*'}	//090
};

unsigned char ScanCodesSp[MAX_CODES][2] =	{
		
	{NADA,NADA},/*Escape*/{ESCAPE,ESCAPE},

	{'!','1'},{'"','2'},{0xF9,'3'},{'$','4'},{'%','5'}, {'&','6'},
	{'/','7'},{'(','8'},{')','9'},{'=','0'},{'?','\''},{0xA8,0xAD},

	/*BACKSPACE*/	{'\b','\b'},
	/*TAB*/		{'\t','\t'},

	{'Q','q'},{'W','w'},{'E','e'},{'R','r'},{'T','t'},{'Y','y'},{'U','u'},
	{'I','i'},{'O','o'},{'P','p'},{'^','`'},{'*','+'},

	/*Enter*/	{'\n','\n'},
	/*CTRL IZQ*/	{NADA,NADA},

	{'A','a'},{'S','s'},{'D','d'},{'F','f'},{'G','g'},{'H','h'},{'J','j'},
	{'K','k'},{'L','l'},{165, 164}/*{0xA5,0xA4}*/,{NADA,NADA},/*{'š','Ž'}*/{0xA6,0xA7},

	/*Shift Izquierdo*/{NADA,NADA},{0x80,0x87},
	/*{NADA,NADA,NADA},{0x80,0x87,'}'},*/

	{'Z','z'},{'X','x'},{'C','c'},{'V','v'},{'B','b'},{'N','n'},{'M','m'},
	{';',',',},{':','.'},{'_','-'},

	/*Shift Derecho*/	{NADA,NADA},{'*','+'},
	/*ALT IZQ*/		{NADA,NADA},
	/*Espacio*/		{' ',' '},
	/*CAPSLOCK*/		{NADA,NADA},

	/*F1*/	{NADA,NADA},{NADA,NADA},{NADA,NADA},{NADA,NADA},{NADA,NADA},
		{NADA,NADA},{NADA,NADA},{NADA,NADA},{NADA,NADA},{NADA,NADA},

	/*NUM LOCK*/	{NADA,NADA},
	/*SCROLL LOCK*/	{NADA,NADA},
	
	/*Key Pad*/
	
	{'7','7'},{'8','8'},{'9','9'},{'-','-'},
	{'4','4'},{'5','5'},{'6','6'},{'+','+'},
	{'1','1'},{'2','2'},{'3','3'},{'0','0'},
	{'.','.'},{NADA,NADA},{'+','*'},{'+','*'},
	
	/*F11*/{NADA,NADA},
	{NADA,NADA},//088 F12
	{'+','*'},	//089
	{'+','*'}	//090
};

/*Acento español*/
unsigned char Acen_esp[5][2] ={
	{0xA0,0xA0},{0x82,0x82},{0xA1,0xA1},{0xA2,0xA2},{0xA3,0xA3}
};

/*Acento frances*/
unsigned char Acen_fra[5][2] ={
	{0x85,0x85},{0x8A,0x8A},{0x8D,0x8D},{0x95,0x95},{0x97,0x97}
};


static int prueba = 1;

void int_21(int code) 
{
	int vocal;

	idioma_teclado=SP;

	if(!tecl.size <= BUFFER_SIZE)
	{	/* seteo el shift */
		if(code == 0x2A || code == 0x36){
			shift = 0;
		}
		else if( code == 0x2A+0x80 || code == 0x36+0x80){
			shift = 1;
				
		}
		/* seteo el block_may */
		else if(code == 0x3A){
			block_may = ! block_may;
		}		
		
		else if(code == 0x1A)
		{

			acento_esp=1;
			return;
			
		}
		/* filtro los caracteres no soportados */
		else /*if((code >= 0x02 && code <= 0x0D) || (code >= 0x0F && code <= 0x1B)
		|| (code >= 0x1E && code <= 0x29) || (code >= 0x2B && code <= 0x35) 
		|| code == 0x39 || code == 0x1C
		|| code == 0x0E || code==0xA0 || code== 0xA1 || code==0xA2 
		|| code==0xA3|| code==0x82 || code==0x28){*/
		if (code <= 0x82 || (code <= 0xA3 && code >= 0xA0)){
			
			if(idioma_teclado == ENG)
			{
			tecl.buf[tecl.write] = ScanCodesEn[code][shift&&block_may];
				tecl.write ++;
				tecl.size ++;
				if(tecl.write >= BUFFER_SIZE)
				{
					tecl.write = 0;
				}
			}
			else if (idioma_teclado == SP)
			{					
				if ((acento_esp == 1) && ((vocal=esVocal(code))!=-1))
				{	

					tecl.buf[tecl.write] = Acen_esp[vocal][shift&&block_may];
					tecl.write ++;
					tecl.size ++;
					if(tecl.write >= BUFFER_SIZE)
					{
						tecl.write = 0;
					}
				}
				else{
					tecl.buf[tecl.write] = (unsigned char)ScanCodesSp[code][shift&&block_may];
					tecl.write ++;
					tecl.size ++;
					if(tecl.write >= BUFFER_SIZE)
					{
						tecl.write = 0;
					}
				}

				acento_esp=0;
				
			}
		} 
	}
	return;
}

byte next_char (){
	byte a;

	if(tecl.size > 0) {
	
		a=tecl.buf[tecl.read];
		tecl.read++;
		tecl.size--;

		if(tecl.read >= BUFFER_SIZE)
		{
			tecl.read = 0;
		}
		return a;
	}
	else
	{
		return 0;
	}
}


int
esVocal(unsigned char letra)
{
	switch(letra)
	{
		case 0x1E:
			return 0;
		case 0x12:
			return 1;
		case 0x17:
			return 2;
		case 0x18:
			return 3;
		case 0x16:
			return 4;
		default: return -1;
	}

}


