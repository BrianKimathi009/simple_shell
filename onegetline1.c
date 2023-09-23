#include "shell.h"

/**
 * input_bfr - this function buffers chained commands
 * @info: structure param
 * @buf: buffers address
 * @len: length variable address
 *
 * Return: num of bytes read
 */
ssize_t input_bfr(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t lenth_q = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, siginalhndlr);
#if USE_GETLINE
		s = getline(buf, &lenth_q, stdin);
#else
		s = s_getline(info, buf, &lenth_q);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			erase_com(*buf);
			creat_hist_slist(info, *buf, info->histcount++);
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * ret_input - this functon gets a line having removeed the newline
 * @info: structure param
 *
 * Return: num of bytes read
 */
ssize_t ret_input(info_t *info)
{
	static char *buf;
	static size_t k, l, xtent;
	ssize_t s = 0;
	char **bfr_q = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	s = input_bfr(info, &buf, &xtent);
	if (s == -1)
		return (-1);
	if (xtent)
	{
		l = k;
		p = buf + k;

		chck_grp(info, buf, &l, k, xtent);
		while (l < xtent)
		{
			if (s_grp(info, buf, &l))
				break;
			l++;
		}

		k = l + 1;
		if (k >= xtent)
		{
			k = xtent = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*bfr_q = p;
		return (s_strlen(p));
	}

	*bfr_q = buf;
	return (s);
}

/**
 * rd_bfr - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t rd_bfr(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->readfd, buf, READ_BUF_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}

/**
 * s_getline - gets the next line of input from STDIN
 * @info: structure pram
 * @ptr: pointer to buffer address
 * @length: buffer lenth
 *
 * Return: s
 */
int s_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, xtent;
	size_t l;
	ssize_t t = 0, s = 0;
	char *q = NULL, *nw_q = NULL, *d;

	q = *ptr;
	if (q && length)
		t = *length;
	if (j == xtent)
		j = xtent = 0;

	t = rd_bfr(info, buf, &xtent);
	if (t == -1 || (t == 0 && xtent == 0))
		return (-1);

	d = s_strchr(buf + j, '\n');
	l = d ? 1 + (unsigned int)(d - buf) : xtent;
	nw_q = s_realloc(q, s, s ? s + l : l + 1);
	if (!nw_q)
		return (q ? free(q), -1 : -1);

	if (s)
		s_strncat(nw_q, buf + j, l - j);
	else
		s_strncpy(nw_q, buf + j, l - j + 1);

	s += l - j;
	j = l;
	q = nw_q;

	if (length)
		*length = s;
	*ptr = q;
	return (s);
}

/**
 * sigintHandler - this function blocks C^C
 * @sig_num: signal num
 *
 * Return: void
 */
void signalhndlr(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
