#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define MAX_LINES 10
#define MAX_LENGTH 100

int main()
{
	char savedText[MAX_LINES][MAX_LENGTH];
	int fd, i = 0, j = 0;
	char buf;
	int bytes_read;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1) {
		printf("Error\n");
		return 1;
	}

	while ((bytes_read = read(fd, &buf, 1)) > 0) {
		if (buf == '\n') {
			savedText[i][j] = '\0';
			i++;
			j = 0;
		} else {
			savedText[i][j++] = buf;
		}
		if (i >= MAX_LINES) break;
	}

	close(fd);

	printf("File read success\n");

	int total_lines = i;

	printf("Total lines: %d\n", total_lines);


	char input[20];
	printf("You can choose 1 ~ 4 Line\n");
	printf("Pls 'Enter' the line to select : ");
	scanf("%s", input);

	if (strcmp(input, "*") == 0) {
		for (i = 0; i < total_lines; i++) {
			printf(" %s\n", savedText[i]);
		}
	} else if (strchr(input, '-') != NULL) {
		int start, end;
		sscanf(input, "%d-%d", &start, &end);
		for (i = start - 1; i < end && i < total_lines; i++) {
			printf("%s\n", savedText[i]);
		}
	} else if (strchr(input, ',') != NULL) {
		char *token = strtok(input, ",");
		while (token != NULL) {
			int line_num = atoi(token) - 1;
			if (line_num >= 0 && line_num < total_lines) {
				printf("%s\n", savedText[line_num]);
			}
			token = strtok(NULL, ",");
		}
	} else {
		int line_num = atoi(input) - 1;
		if (line_num >= 0 && line_num < total_lines) {
			printf("%s\n", savedText[line_num]);
		} else {
			printf("Error");
		}
	}

	return 0;
}
