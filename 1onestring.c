#include "shell.h"

/**
 * s_strlen - this function returns string's length
 * @s: string to be checked
 *
 * Return: string length
 */
int s_strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * s_strcmp - this function compares 2 strings
 * @s1: 1st string
 * @s2: 2nd string
 *
 * Return: -ve if s1 < s2, +ve if s1 > s2, 0 if s1 == s2
 */
int s_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * s_strstr - looks for needle in haystack
 * @haystack: string to be searched
 * @needle: substring to look for
 *
 * Return: next char's address in haystack
 */
char *s_strstr(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * s_strcat - this functionconcats 2 strings
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to dest
 */
char *s_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (result);
}
