#include "main.h"

/**
 * print_env - print the current environment
 * @env: the environment arg
 */
void print_env(char **env)
{
	/*extern char **environ;*/

	/* pointer to the environment variables array */
	int i; /* index variable */

	for (i = 0; env[i] != NULL; i++)
	/* loop through all environment variables */
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		/* write the environment variable to stdout */
		write(STDOUT_FILENO, "\n", 1); /* write a new line to stdout */
	}
}
