#include "sharrot_shell.h"

#define YELLOW "\033[33m"
#define RESET "\033[0m"

/**
 * _run_strtok - Runs main strtok.
 *
 * @list: list of args.
 *
 * @list_size: size of list of args.
 *
 * @line: input.
 *
 * Return: reallocated char pointer.
 */
static char **_run_strtok(char **list, size_t *list_size, char *line)
{
	char *token;
	int i;
	size_t to_realloc;

	token = strtok(line, " \n\t");

	for (i = 0; token; i++)
	{
		*list_size += 1;
		to_realloc = sizeof(char *) * *list_size;
		list = realloc(list, to_realloc);
		if (!list)
		{
			for (i -= 1; i >= 0; i--)
				free(list[i]);
			free(line);
			free(token);
			exit(69);
		}

		list[i] = strdup(token);
		if (!list[i])
		{
			for (i -= 1; i >= 0; --i)
				free(list[i]);
			free(line);
			free(token);
			free(list);
			exit(69);
		}

		token = strtok(NULL, " \n\t");
	}

	list[*list_size - 1] = NULL;

	return (list);
}


/**
 * main - Can work in two ways:
 *	If it gets args it passes those args to sharrot() wo looping.
 *	Else loops, each enter gets read and passed to sharrot().
 *
 * @ac: n of args.
 * @av: args.
 *
 * Return: 0 if successful, else is error.
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len;
	ssize_t result2;
	char **list;
	size_t list_size;
	int i;
	int result;

	if (ac > 1)
	{
		for (i = 0; i + 1 < ac; i++)
			av[i] = av[i + 1];
		av[i] = NULL;
		sharrot(av);
		return (0);
	}
	list = malloc(sizeof(char *));
	while (1)
	{
		printf("%sSharrot%s$ ", YELLOW, RESET);
		result2 = getline(&line, &len, stdin);

		if (result2 == -1)
			break;

		list_size = 1;
		list = realloc(list, sizeof(char *));
		list = _run_strtok(list, &list_size, line);

		result = sharrot(list);

		for (i = 0; list[i]; i++)
			free(list[i]);
		if (result == -2)
			break;
	}
	free(line);
	free(list);
	return (0);
}
