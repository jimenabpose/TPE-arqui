#include "../include/defs.h"
#include "../include/kasm.h"
#include "../include/cpu_info.h"
#include "../include/keyboard.h"
#include "../include/stdio.h"
#include "../include/shell.h"
#include "../include/string.h"


extern int cursor;

void divCeroInt(){
	int a=3/0;
}




void general_protection(){
	_general_protection();
}


void
inicializarPantalla()
{
	cursor = 0;
	
	printf("Bienvenido a Johnelite");
	print_enter();
	printf("Si necesita ayuda tipee el comando 'ayuda'");
	print_enter();
	print_enter();
}

void
separaPorEspacios(char *s, char out[][LONG_STR_TKN])
{
	int i, j;

	/* out[0]= direccion para guardar comando */
	/* out[1]= direccion para guardar parametro */

	while( *s == ' ' )
		s++;

	for(i=0, j=0; s[i] != ' ' && s[i] != 0 && j<LONG_STR_TKN; i++, j++)
		out[0][j] = s[i];
	out[0][j]=0;

	while( s[i] == ' ' )
		i++;

	if( s[i] == 0 )
		return;

	for(j=0; s[i] != 0 && j<LONG_STR_TKN; i++, j++)
		out[1][j] = s[i];
	out[1][j]=0;

	return;
}

/*
** ciclo principal del interprete de comandos
*/

void
funcionPrincipal()
{
	int i;
	unsigned char c;
	int ret;
	int flag = 1;
	char data[2][LONG_STR_TKN];
	char in[LONG_STR_CMD];

	/*tTicks=0;*/
	flush();

	print_new_line();

	while(1)
	{
		/*print_new_line();*/

		do
		{
			//screen_cursor(240+(cursor/2)+1);
			c = next_char();
			/* si es enter */
			if (c < 0x05 | c == 80){
				;
			}else if(c == '\n')
			{
				//print_enter();
				if(i>=LONG_STR_CMD)
				i=LONG_STR_CMD-1;
				in[i]=0;
				separaPorEspacios(in, data);
				ret=llamaFunc(data);
				data[0][0]=data[1][0]=0;
				print_new_line();
				flag = 0;
				i = 0;
			}
			else if(c!=-1){
				
				if(c<0x05 && c != 80)
				;
				/* si no se el backspace */
				else if(c != '\x08')
				{
					if(i<LONG_STR_CMD)						
						in[i]=c;
					
					i++;
					
					printChar(c);
					/*printChar(c);*/
					flush();

					flag = 0;
					
				}
				else if(i > 0){
					i--;
					printChar(c);
					/*printChar(c);*/
					flush();
				}
			}
		}
		while(flag);
		flag = 1;

		
	}
}



int
llamaFunc(char s[2][LONG_STR_TKN])
{
	int cursorBkp;
	int arg_extra=0;

	if(s[0][0]==0)
		return NO_CD;
	else if(!strcmp(s[0], "echo"))
	{
		print_enter();		
		printf(s[1]);
		flush();
		return ECHO_CD;
	}
	else if(!strcmp(s[0], "clear"))
	{
		if(s[1][0]==0)
		{
						
			k_clear_screen();
			return CLEAR_CD;
		}
		else
			arg_extra=1;
	}
	else if(!strcmp(s[0], "garbage"))
	{
		if(s[1][0]==0)
		{
			garbage();
			return GBG_CD;
		}
		else
			arg_extra=1;
	}
	else if(!strcmp(s[0], "uname"))
	{
		if(s[1][0]==0)
		{
			print_enter();
			printf("Johnelite");
			flush();
			return CODE_CD;
		}
		else
			arg_extra=1;
	}
	else if(!strcmp(s[0], "pwd"))
	{
		if(s[1][0]==0)
		{
			print_enter();
			printf("/");
			flush();
			return CODE_CD;
		}
		else
			arg_extra=1;
	}
	else if(!strcmp(s[0], "ls"))
	{
		if(s[1][0]==0)
		{
			print_enter();
			printf("dev      root     home");
			print_enter();
			printf("bin      mnt      boot" );
			print_enter();
			printf("usr      etc      media");
			return CODE_CD;
		}
		else
			arg_extra=1;
	}
	
	else if(!strcmp(s[0], "divCero"))
	{
		if(s[1][0]==0)
		{
			print_enter();
			divCeroInt();
		}
		else
			arg_extra = 1;
	}
	else if(!strcmp(s[0], "gralprotection"))
	{
		if(s[1][0]==0)
		{
			print_enter();
			general_protection();
		}
		else
			arg_extra = 1;
	}

	else if(!strcmp(s[0], "ayuda"))
	{
		if(s[1][0]==0)
		{
			print_enter();
			printf("Johnelite");
			print_enter();
			print_enter();
			printf("echo [argumentos]     imprime los argumentos");
			print_enter();
			printf("clear     borra la pantalla");
			print_enter();
			printf("garbage     imprime basura");
			print_enter();
			printf("uname     imprime el nombre del sistema");
			print_enter();
			printf("pwd     imprime el directorio actual");
			print_enter();
			printf("ls     lista las carpetas del directorio actual");
			print_enter();
			printf("cpuid     imprime informacion sobre el cpu");
			print_enter();
			printf("cpufeatinfo     imprime informacion del feature cuyo indice es pasado como argumento");
			print_enter();
			printf("ayuda     imprime esta pantalla");
			print_enter();
			return CODE_CD;
		}
		else
			arg_extra=1;
	}

	else if(!strcmp(s[0], "cpufeatinfo"))
	{
		print_enter();

		print_feature(atoi(s[1],10));
		return CODE_CD;
		
	}
	
	else if(!strcmp(s[0], "cpuid"))
	{
		if(s[1][0]==0)
		{
			print_enter();
			cpuid();
			return CODE_CD;
		}
		else
			arg_extra=1;
	}


	if(arg_extra==0)
	{
		print_enter();
		printf(s[0]);
		printf(":");
		printf(" comando no encontrado");
		flush();
		return CNF_CD;
	}
	else
	{
		print_enter();
		printf(s[0]);
		printf(":");
		printf(" does not receive arguments");
		flush();
		return CNF_CD;
	}
}




