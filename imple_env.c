#include "main.h"

/**
* print_env - print the current environment
*/
void print_env(void)
{
	extern char **environ;

	/* pointer to the environment variables array */
	int i; /* index variable */

	for (i = 0; environ[i] != NULL; i++)
		/* loop through all environment variables */
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		/* write the environment variable to stdout */
		write(STDOUT_FILENO, "\n", 1); /* write a new line to stdout */
	}
}
