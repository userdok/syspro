#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 100

void upper(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - ('a' - 'A');
		}
	}
}

int main(int argc, char *argv[])
{
	int n, pid, fd[2];
	char line[MAXLINE];

	pipe(fd);

	printf("parent process start\n");

	if ((pid = fork()) == 0)
	{
		close(fd[0]);
		char input[MAXLINE];
		printf("input string: ");
		fgets(input, MAXLINE, stdin);

		input[strcspn(input, "\n")] = 0;

		write(fd[1], input, strlen(input) + 1);
		close(fd[1]);
	} else {
		if (fork() == 0)
		{
			close(fd[1]);
			n = read(fd[0], line, MAXLINE);
			line[n] = '\0';

			upper(line);

			printf("%s\n", line);
			close(fd[0]);
		}
	}
	wait(NULL);
	wait(NULL);
	exit(0);
}
