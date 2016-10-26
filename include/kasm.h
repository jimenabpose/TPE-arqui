/*********************************************
kasm.h

************************************************/


unsigned int    _read_msw();

void            _lidt (IDTR *idtr);

void		_mascaraPIC1 (byte mascara);	/* Escribe mascara de PIC1 */
void		_mascaraPIC2 (byte mascara);	/* Escribe mascara de PIC2 */
void 		_set_pic();

void		_Cli(void);			/* Deshabilita interrupciones  */
void		_Sti(void);			/* Habilita interrupciones  */

void		_int_00_hand();
void		_int_01_hand();
void		_int_02_hand();
void		_int_03_hand();
void		_int_04_hand();
void		_int_05_hand();
void		_int_06_hand();
void		_int_07_hand();
void		_int_08_hand();
void		_int_09_hand();
void		_int_0A_hand();
void		_int_0B_hand();
void		_int_0C_hand();
void		_int_0D_hand();
void		_int_0E_hand();
void		_int_0F_hand();
void		_int_10_hand();
void		_int_11_hand();
void		_int_12_hand();
void		_int_13_hand();

void		_int_20_hand();		/* Timer tick */
void		_int_21_hand();		/* Teclado */
void		_int_80_hand();		

void		_debug (void);

void _stack_overflow(void);
void _general_protection();
void screen_cursor(int cur);
byte _call_int_80(byte write_or_read, byte file_descriptor, dword offset, byte dato);
void _wscreen(char *, int);
void _set_pic(void);



