#include "sharrot_shell.h"
#include <sys/types.h>
#include <sys/wait.h>

/**
 * _run_program - Runs a found program.
 *
 * @path: path
 * @av: args.
 *
 * Return: int
 */
int _run_program(char *path, char **av)
{
	pid_t child_pid;
	static char *newenviron[] = { NULL };
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (-1);
	}

	if (child_pid == 0)
		execve(path, av, newenviron);
	else
		wait(&status);

	return (0);
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
	char *PATH2;
	char *token;
	char buffer[1024] = {0};

	if (!av[0])
		return (-1);
	if (strcmp(av[0], "exit") == 0)
		return (-2);

	sprintf(buffer, "%s", av[0]);
	if (access(buffer, X_OK) == 0)
		return (_run_program(buffer, av));

	PATH2 = getenv("PATH");
	PATH = malloc(_strlen(PATH2));
	_strcpy(PATH, PATH2);
	puts(PATH);
	token = strtok(PATH, ":");
	while (token)
	{
		if (token[_strlen(token) - 1] == '/')
			sprintf(buffer, "%s%s", token, av[0]);
		else
			sprintf(buffer, "%s/%s", token, av[0]);
		puts(buffer);
		if (access(buffer, X_OK) == 0)
		{
			free(PATH);
			return (_run_program(buffer, av));
		}
		token = strtok(NULL, ":");
	}

	free(PATH);
	perror("Command not found.");
	return (1);
}

