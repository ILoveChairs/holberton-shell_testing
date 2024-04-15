#include "sharrot_shell.h"
#include <sys/types.h>
#include <sys/wait.h>

/**
 * _run_program - Runs a found program.
 *
 * @av: args.
 */
void _run_program(char *path, char **av)
{
	pid_t child_pid;
	static char *newenviron[] = { NULL };
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		execve(path, av, newenviron);
	}
	else
	{
		wait(&status);
	}
}

/**
 * sharrot - Searches executables with first arg's name.
 *
 * @av: args
 *
 * Return: 0 if found, 1 if not.
 */
int sharrot(char **av)
{
	char *PATH;
	char *token;
	char buffer[1024] = {0};

	PATH = getenv("PATH");

	token = strtok(PATH, ":");
	while (token)
	{
		sprintf(buffer, "%s/%s", token, av[0]);
		if (access(buffer, X_OK) == 0)
		{
			_run_program(buffer, av);
			return (0);
		}
		token = strtok(NULL, ":");
	}

	return (1);
}

