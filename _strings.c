#include "main.h"

/**
  *_strlen - this fuction calclut the length
  *
  *@s: this is string of char
  *
  *Return: this function return the length
  */
int _strlen(char *s)
{
	int len = 0;

	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}
/**
 *_strcpy - this function to copy a string
 *@dest: the variable to copy in
 *@src: variable to copy from
 *Return: the copy str value
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (*(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}
/**
 *_strcat - this fuction concatenat string with another
 *@dest: this is the destination variable
 *@src: this is the source variable
 *Return: the value of dest after concatenation
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, k = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
	k = 0;
	while (src[k] != '\0')
	{
		dest[i] = src[k];
		k++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcmp - compare two string value
 * @s1: sturng nubmer1
 * @s2: string number2
 *
 * Return: s1[i] - s2[i] or 0 if same
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] > s2[i])
		{
			return (-1);
		}
		else if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}
#include "main.h"

/**
 *_strchr - this function find the chart in pointer
 *
 *@s: this string to be checked
 *@c: char to search for
 *
 *Return: return a poiter of the first occurrence of c if not found null
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	return (NULL);
}
