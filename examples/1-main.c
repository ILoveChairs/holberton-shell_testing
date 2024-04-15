#include "mini_shell.h"

/**
 * main - main
 *
 * @ac: ac
 * @av: av
 *
 * Return: 0
 */
int main(__attribute__((unused)) int ac, char **av)
{
	int i;

	for (i = 0; av[i]; i++)
	{
		printf("%s\n", av[i]);
	}

	return (0);
}



