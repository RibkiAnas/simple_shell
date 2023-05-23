#include "main.h"

/**
* exit_shell - exit the shell
* @line: the line from stdin to be free
*/
void exit_shell(char *line)
{
	free(line);
	exit(0);
}
