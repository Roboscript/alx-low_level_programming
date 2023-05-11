#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *my_buffer(char *filename);
void close_file(int fd);

/**
 * my_buffer - creates a buffer that reads 1024 bytes at a time.
 * @filename: The name of the file buffer is storing chars for.
 *
 * Return: A pointer to the new buffer.
 *
 * Description: This function has a buffer of 1024 size
 */
char *my_buffer(char *filename)
{
	char *buffer;

	buffer = malloc(sizeof(char) * 1024);

	if (buffer == NULL)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", filename);
		exit(99);
	}

	return (buffer);
}

/**
 * close_file – Closes file descriptors.
 * Description: This closes the file
 * @fd: The file to be closed.
 */
void close_file(int fd)
{
	int cf;

	cf = close(fd);

	if (cf == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main – Copy content from 1 file to the other file.
 * @argc: arguments supplied to the function.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the argument count is incorrect - exit code 97.
 * If file_from does not exist or cannot be read - exit code 98.
 * If file_to cannot be created or written to - exit code 99.
 * If file_to or file_from cannot be closed - exit code 100.
 */
int main(int argc, char *argv[])
{
	int cfrom, cto, rd, wt;
	char *buffer;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	buffer = my_buffer(argv[2]);
	cfrom = open(argv[1], O_RDONLY);
	rd = read(cfrom, buffer, 1024);
	cto = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

	do {
		if (cfrom == -1 || rd == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't read from file %s\n", argv[1]);
			free(buffer);
			exit(98);
		}

		wt = write(cto, buffer, rd);
		if (cto == -1 || wt == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", argv[2]);
			free(buffer);
			exit(99);
		}

		rd = read(cfrom, buffer, 1024);
		cto = open(argv[2], O_WRONLY | O_APPEND);

	} while (rd > 0);

	free(buffer);
	close_file(cfrom);
	close_file(cto);

	return (0);
}

