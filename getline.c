#include "sharrot_shell.h"
#define DEBUG

/**
 * _getline - gets line from stdin.
 *
 * @lineptr: line.
 * @n: n
 * @stream: stream.
 *
 * Return: result.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t output;
	int buffer_size = 1024;
	char buffer[buffer_size];
	size_t total_written = 0;

	if (!(*lineptr))
	{
		*lineptr = malloc(8);
		if (!(*lineptr))
			exit(98);
		*n = 8;
	}

	output = 1;
	while (output > 0 && output == 1024)
	{
		output = read(stream->_fileno, buffer, buffer_size);
		_strcpy(*(lineptr + total_written), buffer);
	}

	return (output);
}

#ifdef DEBUG

/**
 * main - main.
 *
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t ret;

	puts("DEBUG: readline\n");

	puts("Reading lines with line already malloc'd:");
	ret = getline(&line, &size, stdin);
	printf("Got: return=%li, line=%s, size=%lu\n", ret, line, size);
	ret = _getline(&line, &size, stdin);
	printf("Got: return=%li, line=%s, size=%lu\n", ret, line, size);

	free(line);
	line = NULL;
	size = 0;

	puts("Reading lines with line not malloc'd:");
	ret = _getline(&line, &size, stdin);
	printf("Got: return=%li, line=%s, size=%lu\n", ret, line, size);
	ret = getline(&line, &size, stdin);
	printf("Got: return=%li, line=%s, size=%lu\n", ret, line, size);

	puts("\nEnding DEBUG");

	free(line);
	return (0);
}

#endif
