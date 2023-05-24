#include "main.h"
/**
*_strdup - this function have a newly allocated space have a copy of str
*@str: this string given
*
*Return: return NULL if : str = NULL;
*/

char *_strdup(char *str)
{
	char *p;
	unsigned int i;
	unsigned int l;

	if (str == NULL)
		return (NULL);
	l = _strlen(str) + 1;
	p = malloc(l);
	if (p == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < l; i++)
	{
		p[i] = str[i];
	}
	return (p);
}
/**
 *_isspace - this function to return if is space or not
 *@c: char to see if space
 *Return: 1 if Character is a whitespace character else 0
 */
int _isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}
/**
 *_strndup - this function to deplucat n char from str
 *@str: string to be dumlcat
 *@n: the n charter to be dup
 *Return: pointer to the now dumop str
 */
char *_strndup(char *str, size_t n)
{
	size_t len = _strlen(str);
	char *new_str;

	if (len > n)
	{
		len = n;
	}

	new_str = malloc((len + 1) * sizeof(char));

	if (new_str == NULL)
	{
		return (NULL);
	}
	_strncpy(new_str, str, len);
	new_str[len] = '\0';

	return (new_str);
}
/**
 * _strncpy - copy a string
 * @dest: input value
 * @src: input value
 * @n: input value
 *
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j;

	for (j = 0; j < n && src[j] != '\0'; j++)
	{
		dest[j] = src[j];
	}
	while (j < n)
	{
		dest[j++] = '\0';
	}

	return (dest);
}

/**
 *_getenv - function to get a env variable value
 *@varenv: this var hold the env varible we want
 *@env: the envaremnt variables all string
 *Return: the value of the specf env varaible
 */
char *_getenv(char *varenv, char **env)
{
	int i;
	char *variable, *delime, *value;

	if (varenv == NULL || env == NULL)
		return (NULL);

	for (i = 0; env[i] != NULL; i++)
	{
		variable = _strdup(env[i]);
		delime = _strchr(variable, '=');
		if (delime == NULL)
		{
			free(variable);
			continue;
		}
		*delime = '\0';
		if (_strcmp(variable, varenv) == 0)
		{
			value = _strdup(delime + 1);
			free(variable);
			return (value);
		}
		free(variable);
	}
	return (NULL);
}
