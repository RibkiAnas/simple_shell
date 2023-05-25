#include "main.h"

/**
 *_getenv - function to get a env variable value
 *@varenv: this var hold the env varible we want
 *@env: the envaremnt variables all string
 *Return: the value of the specf env varaible
 */
char *_getenv(char *varenv, char **env)
{
	size_t varlen, envlen;
	char *envvari, *value, *dupl;
	int i;

	if (varenv == NULL || env == NULL)
		return (NULL);

	varlen = _strlen(varenv);

	for (i = 0; env[i] != NULL; i++)
	{
		envvari = env[i];
		envlen = _strcspn(envvari, "=");
		if (varlen == envlen && _strncmp(varenv, envvari, varlen) == 0)
		{
			value = envvari + envlen + 1;
			dupl = _strdup(value);
			if (dupl == NULL)
				return (NULL);
			return (dupl);
		}
	}
	return (NULL);
}
