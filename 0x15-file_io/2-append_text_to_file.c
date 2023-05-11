#include "main.h"

/**
 * append_text_to_file - Function that appends text at the end of a file.
 * @filename: is the name of the file.
 * @text_content: The NULL terminated string to add to the end of the file.
 *
 * Return: If the function fails or filename is NULL - -1.
 *         If the file does not exist or user lacks write permissions - -1.
 *         Otherwise - 1.
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int openf, bnum, length = 0;

	if (filename == NULL)
		return (-1);

	if (text_content != NULL)
	{
		for (length = 0; text_content[length];)
			length++;
	}

	openf = open(filename, O_WRONLY | O_APPEND);
	bnum = write(openf, text_content, length);

	if (openf == -1 || bnum == -1)
		return (-1);

	close(openf);

	return (1);
}
