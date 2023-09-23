#include "shell.h"

/**
 *_sputs - outputs an input string
 * @str: string to print
 *
 * Return: Nothing returns
 */
void _sputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_sputchar(str[j]);
		j++;
	}
}

/**
 * _sputchar - this function writes the char c to stderr
 * @c: char to be printed
 *
 * Return: on success 0.
 * on error, -1, and errno is set appropriately
 */
int _sputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putfildes - writes char c to given fildes
 * @c: char to be printed
 * @fd: fildes to write to
 *
 * Return: 1 on success
 * -1 on error, and errno is set appropriately
 */
int _putfildes(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 *_putsfildes - this function prints an input string
 * @str: string to be printed
 * @fd: the fildes to write to
 *
 * Return:num of chars
 */
int _putsfildes(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfildes(*str++, fd);
	}
	return (j);
}
