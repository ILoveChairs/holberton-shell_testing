#include "mini_shell.h"
#define DEBUG

/**
 * read_stat - Reads the stat files and returns ppid.
 *
 * @stat_file: Stat file of the process.
 *
 * Return: Parent process id.
 */
static pid_t read_stat(char *stat_file)
{
	int fd;
	unsigned int i, l, j;
	ssize_t bytes_read;
	char buffer[1024] = {0};
	char sppid[10] = {0};

	fd = open(stat_file, O_RDONLY);
	if (fd == -1)
		exit(98);

	bytes_read = read(fd, buffer, 1024);
	if (bytes_read == -1)
		exit(99);

	fd = close(fd);
	if (fd == -1)
		exit(100);

	for (i = 0, l = 0, j = 0; buffer[j] && i <= 3; j++)
	{
		if (buffer[j] == ' ')
			i += 1;
		else if (i == 3)
			sppid[l++] = buffer[j];
	}

	return (_atoi(sppid));
}

/**
 * _getppid - gets parent process id
 *
 * Return: ppid
 */
pid_t _getppid(void)
{
	pid_t pid, ppid;
	unsigned int pid_len;
	unsigned int i;
	char *stat_file;

	pid = getpid();
	pid_len = _uintlen(pid);

	/* 12 = "proc" + slashes + "stat" + null char */
	stat_file = malloc(pid_len + 12);
	if (!stat_file)
		return (0);

	for (i = 0; i < pid_len + 12; i++)
		stat_file[i] = 0;

	_strcpy(stat_file, "/proc/");
	_utoa(stat_file + 6, pid, pid_len);
	_strcpy(stat_file + 6 + pid_len, "/stat");

	ppid = read_stat(stat_file);

	free(stat_file);
	return (ppid);
}


#ifdef DEBUG
/**
 * main - main
 *
 * Return: 0
 */
int main(void)
{
	pid_t expected, given;

	expected = getppid();
	given = _getppid();

	printf("PID = %u\n", getpid());
	printf("PPID = %u, %u\n", expected, given);
	return (0);
}
#endif
