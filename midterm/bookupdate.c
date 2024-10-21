#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[])
{
	int fd, id;
	char c;
	struct book record;

	printf("--bookupdate--");

	if (argc < 2) {
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}

	if ((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	do {
		if (scanf("%d", &id) == 1) {
			lseek(fd, (long) (id-START_ID)*sizeof(record), SEEK_SET);
			if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
				printf("%d %s %s %d %d %d\n", record.id, record.bookname, record.author);
				scanf("%d", &record.score);
				lseek(fd, (long) -sizeof(record), SEEK_CUR);
				write(fd, (char *) &record, sizeof(record));
			} else printf("Record %d Null\n", id);
		scanf(" %c", &c);
		}
	close(fd);
	exit(0);
}
