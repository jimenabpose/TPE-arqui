/***************************************************
  Defs.h
	
****************************************************/

#ifndef _defs_
#define _defs_

#define byte unsigned char
#define word short int
#define dword int

/* Flags para derechos de acceso de los segmentos */
#define ACS_PRESENT     0x80            /* segmento presente en memoria */
#define ACS_CSEG        0x18            /* segmento de codigo */
#define ACS_DSEG        0x10            /* segmento de datos */
#define ACS_READ        0x02            /* segmento de lectura */
#define ACS_WRITE       0x02            /* segmento de escritura */
#define ACS_IDT         ACS_DSEG
#define ACS_INT_386 	0x0E		/* Interrupt GATE 32 bits */
#define ACS_EXC_386 	0x0F		/* Interrupt GATE 32 bits */

#define ACS_INT         ( ACS_PRESENT | ACS_INT_386 )
#define ACS_EXC         ( ACS_PRESENT | ACS_EXC_386 )


#define ACS_CODE        (ACS_PRESENT | ACS_CSEG | ACS_READ)
#define ACS_DATA        (ACS_PRESENT | ACS_DSEG | ACS_WRITE)
#define ACS_STACK       (ACS_PRESENT | ACS_DSEG | ACS_WRITE)

#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */


#define WRITE 0
#define READ 1
#define FD_PANTALLA 	0 
#define FD_TECLADO		1


#define VIDEO_BUFFER_SIZE 4000
#define VIDEO_MEM_POS 0xB800

#define LONG_STR_TKN 100
#define LONG_STR_CMD 320

#define BUFFER_SIZE 240
#define V_BUFFER_LENGTH 160

#define AUX 0
#define ECHO_CD 1
#define CLEAR_CD 2
#define CNF_CD 3
#define NO_CD 4
#define GBG_CD 5
#define CODE_CD 6

/* Descriptor de segmento */
typedef struct {
  word limit,
       base_l;
  byte base_m,
       access,
       attribs,
       base_h;
} DESCR_SEG;


/* Descriptor de interrupcion */
typedef struct {
  word      offset_l,
            selector;
  byte      cero,
            access;
  word	    offset_h;
} DESCR_INT;

/* IDTR  */
typedef struct {
  word  limit;
  dword base;
} IDTR;

typedef struct {
	unsigned char buf[BUFFER_SIZE];
	int write;
	int read;
	int size;
} teclator;

/*typedef struct {
	char * buf;				/* De donde voy a sacar lo que leo o escribo 
	int type;				/* 0 = Escribo, 1 = Leo 
	int cantCharacters;			/* Cuanto voy a leer o escribir 
	int fd;					/* Donde voy a leer o escribir
} parametersData;*/

#endif

