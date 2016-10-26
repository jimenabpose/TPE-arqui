#ifndef _stdio_
#define _stdio_

#define V_BUFFER_LENGTH 160
#define RED_ALL 0x44

byte int_80(dword op, dword data, dword offset, dword fd);
void write(int fd, const void* buffer, int count);
byte read(int fd, void* buffer, int count);
void puts( const char * str );
void flush();
void check_offset(char label, int count);
void check_screen_scroll(int offset);
void page_roll(int backwards);
void printf ( const char *format, ... );
void printChar( unsigned char ascii );
void print_new_line();
void print_tab();
void k_clear_screen();
void garbage();
void k_clear_screen();

#endif
