#include "printk.h"

#include <stdarg.h>

#include "stddef.h"

/*int printk(char* s)
{
	// TODO: printk should prints to framebuffer if and only if the init system has not been executed yet
	
	// TODO: turn below code into some "strlen" function or something like that
	char* ptr = s;
	while (*ptr != '\0') { ptr++; }
	size_t len = ptr - s;
	// end of "strlen"
	
	return write(s, len);
}*/

int printk(char* format, ...)
{
	va_list ap;
	va_start(ap, format);

	char* ptr;

	char buf[1024];
	size_t i = 0;

	for (ptr = format; *ptr != '\0'; ptr++)
	{
		if (*ptr++ == '%')
		{
			switch (*ptr)
			{
				case 's':
					char* sub_ptr;
					for (sub_ptr = va_arg(ap, char*); *sub_ptr != '\0'; sub_ptr++) { buf[i++] = *sub_ptr; }
					break;
			}
		}
		else
		{
			buf[i++] = *ptr++;
		}
	}

	va_end(ap);

	return write(buf, i);
}
