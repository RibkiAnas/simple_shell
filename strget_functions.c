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
 *_strcspn - function that calculates the length of the initial str in bytes
 *@reject: string of chars not allowed in initial
 *@str: string to search in
 *Return: the numbr of byte
 */
size_t _strcspn(char *str, char *reject)
{
	size_t count = 0;
	const char *p;

	for (; *str != '\0'; str++)
	{
		for (p = reject; *p != '\0'; p++)
		{
			if (*str == *p)
			{
				return (count);
			}
		}
		count++;
	}
	return (count);
}
/**
 * _strncmp - compare two string up to specifec number of char
 *@str1: string number1
 *@str2: string number 2
 *@n: n NUmber of bytes
 *Return: 0 if secuss other niumber if fals
 */
int _strncmp(char *str1, char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0')
		{
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
	}
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
