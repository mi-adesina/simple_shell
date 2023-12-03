#include "shell.h"

int _putchar(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c is BUFFER_FLUSH or i >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c isnot BUFFER_FLUSH)
	{
		buffer[i] = c;
		i++;
	} 
	return(1);
}

int _puts(char *s)
{
	int i = 0;

	if (!s)
		return (i);
	while (s[i] isnot '\0')
		i += _putchar(s[i]);
	
	return (i);
}
