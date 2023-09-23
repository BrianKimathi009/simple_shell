#include "shell.h"

/**
 * *s_strncpy - this function copies a string
 * @dest: destination to copy to
 * @src: source to copy from
 * @n: total chars to be counted
 * Return: the concatenated string
 */
char *s_strncpy(char *dest, char *src, int n)
{
	int k, l;
	char *t = dest;

	k = 0;
	while (src[k] != '\0' && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		l = k;
		while (l < n)
		{
			dest[l] = '\0';
			l++;
		}
	}
	return (t);
}

/**
 **s_strncat - this function concats two strings
 *@dest: destination string
 *@src: source string
 *@n: total bytes to be used
 *Return: concatenated string
 */
char *s_strncat(char *dest, char *src, int n)
{
	int k, l;
	char *t = dest;

	k = 0;
	l = 0;
	while (dest[k] != '\0')
		k++;
	while (src[l] != '\0' && l < n)
	{
		dest[l] = src[l];
		k++;
		l++;
	}
	if (l < n)
		dest[k] = '\0';
	return (t);
}

/**
 **s_strchr - this function finds a char in a string
 *@s: string to parse
 *@c: char to look for
 *Return: s
 */
char *s_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
