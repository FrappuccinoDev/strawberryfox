#include "fb.h"

#include "io.h"

char* fb_pointer = (char*)0x000B8000;
size_t fb_cursor = 0;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	fb_pointer[i] = c;
	fb_pointer[i + 1] = ((fg & 0x0f) << 4) | (bg & 0x0f);
}

void fb_move_cursor(unsigned short pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00ff));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos & 0x00ff);
}

void fb_clear()
{
	size_t i;
	for (i = 0; i < FB_MEM_LEN; i += 2) { fb_write_cell(i, ' ', FB_WHITE, FB_BLACK); }
	fb_move_cursor(0);
}

int write(char* buf, size_t len)
{
//	size_t i;
//	for (i = 0; i < len; i++)
	char* ptr;
	for (ptr = buf; *ptr != '\0'; ptr++)
	{
		fb_write_cell(fb_cursor, /*buf[i]*/ *ptr, FB_WHITE, FB_BLACK);
		fb_cursor += 2;
		if (fb_cursor >= FB_MEM_LEN) { fb_move_cursor(fb_cursor = 0); }
	}

	fb_move_cursor(fb_cursor);

	return len;
}
