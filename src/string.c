/*
 * Funciones para manipular strings. El codigo de itoa fue extraido de:
 *
 *				Multiboot Specification
 *				Free Software Foundation
 *				last updated June 24, 2006
 *				http://www.gnu.org/software/grub/manual/multiboot/
 */

void
itoa (char *buf, int base, int d)
{
	char *p = buf;
	char *p1, *p2;
	char tmp;
	unsigned long ud = d;
	int divisor = 10;
	int remainder;

	/* If %d is specified and D is minus, put '-' in the head. */

	if (base == 'd' && d < 0)
	{
		*p++ = '-';
		buf++;
		ud = -d;
	}
	else if (base == 'x')
	{
		divisor = 16;
	}

	/* Divide UD by DIVISOR until UD == 0. */

	do
	{
		remainder = ud % divisor;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;

	} while (ud /= divisor);

	/* Terminate BUF. */

	*p = 0;

	/* Reverse BUF. */

	p1 = buf;
	p2 = p - 1;

	while (p1 < p2)
	{
		tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}

int
atoi(char *buffer, int base)
{
   int numero = 0;
   int s = 0;
      
   if(buffer == 0)
   {
      return -1;
   }
      
   while(*buffer != '\0')
   {         
      if(*buffer >= '0' && *buffer <= '9')
      {
         s = *buffer - '0';   
         numero = (numero* base) + s;
      }
      buffer++;
   }
   return numero;
}

int
strcmp(char* s,char* t)
{
	int i;
	for( i = 0; s[i] == t[i]; i++ )
	{
		if( s[i] == '\0' )
			return 0;
	}
	return s[i] - t[i];
}

void
strcpy ( char* destino, char* fuente )
{
    while( *fuente != 0 )
	{
        *destino = *fuente;
        destino++;
        fuente++;
    }
    *destino = 0;
    return;
}

int
strlen(char* cadena)
{
    int resp=0;
    while(*cadena!=0)
	{
        cadena++;
        resp++;	
    }
    return resp;
}
