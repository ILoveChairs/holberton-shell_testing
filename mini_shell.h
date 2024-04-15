#ifndef _MINI_SHELL_
#define _MINI_SHELL_

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/* str_tools.c */
unsigned int _pow(unsigned int, unsigned int);
unsigned int _strlen(char *);
unsigned int _uintlen(unsigned int);
char *_strcpy(char *, char *);
char *_utoa(char *str, unsigned int uinteger, unsigned int ulen);
int _atoi(char *s);

/* 0-get_ppid */
pid_t _getppid(void);

#endif
