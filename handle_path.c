#include "main.h"

/**
* find_path - find the full path of a
* command using PATH environment variable
* @command: command.
*
* Return: full path of a command using PATH
* environment variable.
*/
char *find_path(char *command)
{
	char *path_env; /* pointer to PATH environment variable value */
	char *path_copy; /* copy of path_env for strtok usage */
	char *dir; /* pointer to a directory in PATH */
	char *full_path; /* pointer to the full path of the command */

	if (command == NULL || command[0] == '\0') /* invalid command name */
		return (NULL);
	if (_strchr(command, '/') != NULL) /* command name contains a slash */
	{
		if (file_exists(command)) /* file exists and is executable */
			return (command);
		else
			return (NULL);
	}
	path_env = getenv("PATH"); /* get the value of PATH environment variable */
	if (!path_env) /* PATH not set */
		return (NULL);
	path_copy = strdup(path_env); /* make a copy of path_env for strtok usage */
	if (!path_copy) /* error in strdup */
		return (NULL);
	dir = strtok(path_copy, PATH_DELIM); /* get the first directory in PATH */
	while (dir) /* loop through all directories in PATH */
	{
		full_path = malloc(_strlen(dir) + _strlen(command) + 2);
		if (!full_path) /* error in malloc */
			return (NULL);
		/* concatenate the directory and the command with a slash */
		_strcat(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, command);
		if (file_exists(full_path)) /* file exists and is executable */
		{
			free(path_copy); /* free the copy of path_env */
			return (full_path); /* return the full path */
		}
		free(full_path); /* free the full path */
		dir = strtok(NULL, PATH_DELIM); /* get the next directory in PATH */
	}
	free(path_copy); /* free the copy of path_env */
	return (NULL); /* command not found in PATH */
}

/**
* file_exists - check if a file exists and is executable
* @path: path of the file.
*
* Return: 1 if a file exists, 0 if not
*/
int file_exists(char *path)
{
	/* file exists and is executable */
	if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		return (1);
	else
		return (0);
}
