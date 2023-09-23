#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
int loct_bltn(info_t *);
void loct_command(info_t *);
void frk_command(info_t *);

int s_command(info_t *, char *);
char *dplc_schar(char *, int, int);
char *loct_spth(info_t *, char *, char *);

int loophsh(char **);


void _sputs(char *);
int _sputchar(char);
int _putfildes(char c, int fd);
int _putsfides(char *str, int fd);

int s_strlen(char *);
int s_strcmp(char *, char *);
char *s_strstr(const char *, const char *);
char *s_strcat(char *, char *);

char *s_strcpy(char *, char *);
char *s_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *s_strncpy(char *, char *, int);
char *s_strncat(char *, char *, int);
char *s_strchr(char *, char);

char **s_strtok(char *, char *);
char **s_strtokr(char *, char);

char *s_memset(char *, char, unsigned int);
void gfree(char **);
void *s_realloc(void *, unsigned int, unsigned int);

int sfree(void **);

int s_intrctive(info_t *);
int s_delimtr(char, char *);
int s_isalphabt(int);
int s_atoi(char *);

int s_erroratoi(char *);
void output_error(info_t *, char *);
int output_d(int, int);
char *change_num(long int, int, int);
void erase_com(char *);

int _theexit(info_t *);
int _thecd(info_t *);
int _theassist(info_t *);

int _thehist(info_t *);
int _thealias(info_t *);

ssize_t get_input(info_t *);
int s_getline(info_t *, char **, size_t *);
void siginalhndlr(int);

void del_data(info_t *);
void enable_data(info_t *, char **);
void rel_data(info_t *, int);

char *s_getenv(info_t *, const char *);
int _theenvr(info_t *);
int _thesetenv(info_t *);
int _theunsetenv(info_t *);
int pop_env_slist(info_t *);

char **acq_environ(info_t *);
int s_unsetenv(info_t *, char *);
int s_setenv(info_t *, char *, char *);

char *acq_hist_sfile(info_t *info);
int input_hist(info_t *info);
int rd_hist(info_t *info);
int creat_hist_slist(info_t *info, char *buf, int linecount);
int rnum_hist(info_t *info);

list_t *calc_snode(list_t **, const char *, int);
list_t *calc_snode_end(list_t **, const char *, int);
size_t output_file_str(const list_t *);
int erase_snode_t_indx(list_t **, unsigned int);
void rel_slist(list_t **);

size_t slst_lenth(const list_t *);
char **slst_t_strng(list_t *);
size_t output_slst(const list_t *);
list_t *snode_begn_wth(list_t *, char *, char);
ssize_t acq_snode_indx(list_t *, list_t *);

int s_grp(info_t *, char *, size_t *);
void chck_grp(info_t *, char *, size_t *, size_t, size_t);
int restore_aka(info_t *);
int restore_vrs(info_t *);
int restore_strng(char **, char *);

#endif
