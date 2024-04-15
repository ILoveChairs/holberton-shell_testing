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
char *_utoa(char *, unsigned int, unsigned int);
int _atoi(char *);

/* int_tools.c */
unsigned int _pow(unsigned int, unsigned int);
unsigned int _uintlen(unsigned int);

/* get_ppid.c */
pid_t _getppid(void);

/* sharrot.c */
int _run_program(char *, char **);
int sharrot(char **);

/* main.c */

#endif
