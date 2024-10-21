#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[])
{
	int fd;
	struct book recode;
	if (argc < 2) {
		fprintf(stderr, "How to use %s file\n", argv[0]);
		exit(1);
	}

	if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	printf("%-2s %-9s %-8s %-4s %-11s %-6s\n","id", "bookName", "author", "year", "numofborrow", "borrow");
	while (scanf("%d %s %s %d %d %d", &recode.id, &recode.bookName, &recode.author, &recode.year, &recode.numofborrow, &recode.borrow) == 6) {
		lseek(fd, (recode.id - START_ID)* sizeof(recode), SEEK_SET);
		write(fd, (char *) &recode, sizeof(recode));
	}
	close(fd);
	exit(0);
}
