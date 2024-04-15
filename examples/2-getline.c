#include "mini_shell.h"

int main(void)
{
	char *line = NULL;
	size_t len;
	size_t n_read;


	printf("$ ");
	n_read = getline(&line, &len, stdin);

	printf("%s", line);

	free(line);

	return (0);
}
