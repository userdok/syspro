#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int line_number = 1;
	int show_line_numbers = 0;

	if (argc > 1 && strcmp(argv[1], "-n") == 0) {
		show_line_numbers = 1;
		argv++;
		argc--;
	}

	for (int i = 1; i < argc; i++) {
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			fprintf(stderr, "Error opening file %s\n", argv[i]);
			continue;
		}

		int c;
		while ((c = fgetc(fp)) != EOF) {
			if (show_line_numbers && (c == '\n' || line_number == 1)) {
				printf("%6d  ", line_number++);
			}
			putchar(c);
		}

		fclose(fp);
	}

	return 0;
}
