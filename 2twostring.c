#include "shell.h"

/**
 * s_strcpy - this funcyion copies a string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to dest
 */
char *s_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * s_strdup -this function duplicates a string
 * @str: string to be duplicated
 *
 * Return: pointer dup string
 */
char *s_strdup(const char *str)
{
	int lenth = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lenth++;
	result = malloc(sizeof(char) * (lenth + 1));
	if (!result)
		return (NULL);
	for (lenth++; lenth--;)
		result[lenth] = *--str;
	return (result);
}

/**
 *_puts - this function inputs a string
 *@str: string to print
 *
 * Return: nothing
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - this function prints a char to the stdin
 * @c: char to print
 *
 * Return: 1 on success, -1 on error, errno is set appropriately
 */
int _putchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
