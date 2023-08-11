#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_next_line(int fd)
{
	char buff_c;
	char *linha;
	char *linha_ptr;

	ssize_t bytesRead;

	linha = malloc(255);
	linha_ptr = linha;
	while ((bytesRead = read(fd, &buff_c, 1)) > 0)
	{
		if (buff_c == '\n')
		{
			*linha = '\0';
			break;
		}
		*linha = buff_c;
		linha++;
	}
	if (bytesRead == 0 && strlen(linha_ptr) == 0)
	{
		free(linha_ptr);
		return NULL;
	}
	return (linha_ptr);
}

int main(void)
{
	char *filename = "testfile";
	int fd = open(filename, O_RDONLY);
	char *linha;

	printf("fd = %d\n\n", fd);

	while ((linha = get_next_line(fd)) != NULL)
	{
		printf("%s\n", linha);
		free(linha);
	}

	return (0);
}
