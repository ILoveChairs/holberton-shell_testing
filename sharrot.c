#include "sharrot_shell.h"

/**
 * _run_program - Runs a found program.
 *
 * @av: args.
 */
void _run_program(char **av)
{
	printf("Executable recognized: %s\n", av[0]);
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
			_run_program(av);
			return (0);
		}
		token = strtok(NULL, ":");
	}

	return (1);
}

