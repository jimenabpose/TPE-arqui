#include "../include/defs.h"
#include "../include/video.h"

byte bufferVideo[VIDEO_BUFFER_SIZE]={0};
char* video = (char*)VIDEO_MEM_POS;


void write_screen(byte c, int offset){
	if(offset<VIDEO_BUFFER_SIZE && offset>=0) {
		bufferVideo[offset] = c;
		_wscreen(c,offset);
	}
}

byte read_screen(){
	byte c;
 	static int buf_cursor = 0;
	c = bufferVideo[buf_cursor++];
    	
	if (buf_cursor >= VIDEO_BUFFER_SIZE)
		buf_cursor = 0;
    	return c;
}

