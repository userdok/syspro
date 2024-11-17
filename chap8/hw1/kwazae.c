#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	char input;
	char** ptr;
	extern char** environ;

	if (argc > 1) {
		input = argv[1][1];
	}
	else {
		fprintf(stderr, "Error\n");
		exit(1);
	}

	if (input == 'e'){
		if (argc == 2) {
			for (ptr = environ; *ptr != NULL; ptr++)
				printf("%s \n", *ptr);
			exit(0);
		}
		else if (argc == 3) {
			ptr = getenv(argv[2]);
			if (ptr != NULL)
				printf("%s = %s \n", argv[2], ptr);
			exit(0);
		}
	}
	else if (input == 'u') {
		printf("My Realistic User ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
		printf("My Valid User ID : %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
		exit(0);
	}
	else if (input == 'g') {
		printf("My Realistic Group ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
		printf("My Valid Group ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
		exit(0);
	}
	else if (input == 'i') {
		printf("my process number : [%d] \n", getpid());
		exit(0);
	}
	else if (input == 'p') {
		printf("my parent's number : [%d] \n", getppid());
		exit(0);
	}
}
