#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
	int fd;
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1) {
		perror("Error");
		return 1;

	}

	bytes_read = read(fd, buffer, BUFFER_SIZE -1);
	if (bytes_read == -1) {
		perror("Error");
		close(fd);
		return 1;
	}

	buffer[bytes_read] = '\0';

	close(fd);

	char *lines[BUFFER_SIZE];
	int line_count = 0;

	char *line = strtok(buffer, "\n");
	while (line != NULL) {
		lines[line_count++] = line;
		line = strtok(NULL, "\n");
	}

	for (int i = line_count - 1; i >= 0; i--) {
		printf("%s\n", lines[i]);
	}

	return 0;
}
