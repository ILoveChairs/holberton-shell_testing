#ifndef _SHARROT_SHELL_
#define _SHARROT_SHELL_

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* str_tools.c */
unsigned int _strlen(char *);
char *_strcpy(char *, char *);
char *_utoa(char *str, unsigned int uinteger, unsigned int ulen);
int _atoi(char *s);

/* int_tools.c */
unsigned int _pow(unsigned int, unsigned int);
unsigned int _uintlen(unsigned int);

/* get_ppid.c */
pid_t _getppid(void);

/* sharrot.c */
void _run_program(char **av);
int sharrot(char **av);

/* main.c */

#endif
