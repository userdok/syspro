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
	
	if (argc < 2) {
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}

	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror (argv[1]);
		exit(2);
	}

	do {
		if (scanf("%d", &id) == 1) {
			lseek(fd, (id-START_ID)*sizeof(recode), SEEK_SET);
			if ((read(fd, (char *) &recode, sizeof(recode)) > 0) && (recode.id != 0)) {
				printf("id\tbookname\tauthor\tyear\tnumofborrow\tborrow\n");
				printf("%d %s %s %d %d %d\n", record.id, record.bookname, recode.author, recode.year, recode.numofborrow, recode.borrow);
			}
			else printf("Record %d Null\n", id);
		} else printf("Input Error");
		
		close(fd);
		exit(0);
	}
