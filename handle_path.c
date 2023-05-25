#include "main.h"

/**
 * get_path_env - gets the value of the PATH environment variable
 * @env: the environment arg
 *
 * Return: a copy of the value of the PATH environment variable,
 * NULL if PATH is not set or an error occurs
 */
char *get_path_env(char **env)
{
	char *path_env; /* pointer to PATH environment variable value */

	(void)env;

	path_env = _getenv("PATH"); /* get the value of PATH env variable */
	if (!path_env)			 /* PATH not set */
		return (NULL);
	return (_strdup(path_env));
}

/**
 * find_path - find the full path of a
 * command using PATH environment variable
 * @command: command.
 * @env: the environment arg
 *
 * Return: full path of a command using PATH
 * environment variable.
 */
char *find_path(char *command, char **env)
{
	char *path_copy, *dir, *full_path; /* copy of path_env for strtok usage */
	int i = 0, j = 0;

	if (command == NULL || command[0] == '\0') /* invalid command name */
		return (NULL);
	if (_strchr(command, '/') != NULL) /* command name contains a slash */
	{
		if (file_exists(command)) /* file exists and is executable */
			return (_strdup(command));
		else
			return (NULL);
	}
	path_copy = get_path_env(env); /* make a copy of path_env for strtok usage */

	if (!path_copy) /* error in _strdup */
		return (NULL);
	/* loop through all directories in PATH */
	while (path_copy[i] != '\0')
	{
		j = i;
		while (path_copy[j] != ':' && path_copy[j] != '\0')
			j++;
		dir = _strndup(path_copy + i, j - i);
		full_path = build_full_path(dir, command);
		if (!full_path) /* error in malloc */
			return (NULL);
		if (file_exists(full_path)) /* file exists and is executable */
		{
			free(path_copy);    /* free the copy of path_env */
			free(dir);	    /* free the directory string */
			return (full_path); /* return the full path */
		}
		free(full_path); /* free the full path */
		free(dir);
		i = j; /* Move to next directory in PATH */
		if (path_copy[i] != '\0')
			i++;
	}
	free(path_copy); /* free the copy of path_env */
	return (NULL);	 /* command not found in PATH */
}

/**
 * build_full_path - build the full path of a command given a
 * directory and command
 * @dir: directory.
 * @command: command.
 *
 * Return: full path of a command given a directory and command.
 */
char *build_full_path(char *dir, char *command)
{
	char *full_path; /* pointer to the full path of the command */

	full_path = malloc(_strlen(dir) + _strlen(command) + 2);
	if (!full_path) /* error in malloc */
		return (NULL);

	/* concatenate the directory and the command with a slash */
	_strcat(full_path, dir);
	_strcat(full_path, "/");
	_strcat(full_path, command);

	return (full_path);
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
