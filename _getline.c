#include "main.h"
/**
 *_getline - this function get the input from the user(STDIN)
 *@buffer: the buffer to full
 *@nread: the size of char read
 *@stdi: the file to read from (usaly from stdin)
 *Return: the Number of char read or EOF(-1)
 */
ssize_t _getline(char **buffer, size_t *nread, FILE *stdi)
{
	size_t counter = 0, new_size, i;
	char c;
	char *tmp;

	if (buffer == NULL || nread == NULL || stdi == NULL)
		return (-1);
	if (*buffer == NULL)
	{
		*buffer = malloc(MAXLINE);
		if (*buffer == NULL)
			return (-1);
		*nread = MAXLINE;
	}
	while ((c = _getchar()) != EOF)
		/*check if c hit the end of line*/
	{
		if (c == '\n')
		{
			(*buffer)[counter] = '\0';
			return (counter);
		}
		if (counter >= *nread - 1) /*1024 reserve for \0 */
		{
			new_size = *nread * 2;
			tmp = malloc(new_size);
			if (tmp == NULL)
				return (-1);
			for (i = 0; i < counter; i++)
				tmp[i] = (*buffer)[i];
			free(*buffer);
			*buffer = tmp;
			*nread = (i + 2);
		}
		(*buffer)[counter] = c;
		counter++;
	}
	if (c == EOF && counter == 0)
		return (EOF);
	(*buffer)[counter] = '\0';
	return (counter);
}

/**
 *_getchar - this function return a char form STDIN
 *
 * Return: char from STDIN
 */
int _getchar(void)
{
	static int read_count;
	static char line_buff[READONCE];
	static int index;


	if (index >= read_count)
	{
		index = 0;
		read_count = read(STDIN_FILENO, line_buff, READONCE);
		if (read_count <= 0)
			return (EOF);
	}
	return (line_buff[index++]);
}
