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

	token = strtok(line, " ");

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

		token = strtok(NULL, " ");
	}

	list[*list_size - 1] = NULL;

	return (list);
}

/**
 * _remove_newline - removes \n at the end of a string.
 *
 * @str: string.
 */
static void _remove_newline(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
		;

	i -= 1;

	if (str[i] == '\n')
		str[i] = ' ';
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
	char **list;
	size_t list_size;
	int i;

	if (ac > 1)
	{
		for (i = 0; i + 1 < ac; i++)
			av[i] = av[i + 1];
		av[i] = NULL;
		sharrot(av);
		return (0);
	}

	printf("%sSharrot%s$ ", YELLOW, RESET);
	getline(&line, &len, stdin);

	_remove_newline(line);

	list_size = 1;
	list = malloc(sizeof(char *));

	list = _run_strtok(list, &list_size, line);

	free(line);

	sharrot(list);

	for (i = 0; list[i]; i++)
		free(list[i]);
	free(list);

	return (0);
}